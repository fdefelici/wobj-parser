/*
 *
 */

#pragma once
#include <stdio.h>
//#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <stdlib.h>

enum wobj_boolean_enum { wobj_false, wobj_true };
typedef unsigned char wobj_bool;

typedef struct {
    float x;
    float y;
    float z;
} wobj_f3;

typedef struct {
    float x;
    float y;
} wobj_f2;

typedef struct {
    wobj_f3 position;
    wobj_f2 uv;
    wobj_f3 normal;
} wobj_vertex;

typedef struct {
    wobj_vertex v1; 
    wobj_vertex v2;
    wobj_vertex v3;
} wobj_triangle;

typedef struct {
    int vertices_count;
    int vertices_size;
    int uvs_size;
    int uvs_count;
    int normals_count;
    int normals_size;
    int faces_count;
    int faces_size;
    float* vertices;
    int* faces;
    float* uvs;
    float* normals;
    wobj_triangle* triangles;
    int triangles_count;
} wobj;

static wobj_bool _string_start_with(const char* a_string, const char* prefix, int prefix_size) {
    return (strncmp(a_string, prefix, prefix_size) == 0);
}

static void _string_split(char* str, const char* delimeter, char* out_tokens[]) {
    char* next_token; //pointer to the remaining sting after the split
    char* token = strtok_s(str, delimeter, &next_token); //assegna il puntatore a partire dal prossimo token (stringa rimanente) 
    int count = 0;
    while(token) {
        out_tokens[count++] = token;
        token = strtok_s(NULL, delimeter, &next_token);
    }
}

static int _wobj_count_starting_with(FILE* file, const char* string_start, int string_size) {
    char buffer[1024];
    int count = 0;
    wobj_bool first_time = wobj_true;
    while(fgets(buffer, sizeof(buffer), file)) {
        //Emulating start_with using: http://www.cplusplus.com/reference/cstring/strncmp/
        if (strncmp(buffer, string_start, string_size) == 0) {
            count++;
            first_time = wobj_false;
        } else if (strncmp(buffer, string_start, string_size) != 0 && !first_time) {
            int n_read = strlen(buffer) + 1;
            fseek(file, -n_read, SEEK_CUR);
            break;
        } 
    }
    return count;
}

static void _wobj_parse_vertices(FILE* file, float* out_vertices) {
    char prefix[] = "v ";
    int prefix_size = 2;
    char buffer[1024]; 
    wobj_bool first_time = wobj_true;
    int count = 0;
    while(fgets(buffer, sizeof(buffer), file)) {
        int n = strlen(buffer);
        if (n == 0) continue;
        //if (n == 0 || buffer[n - 1] != '\n') continue;
        //buffer[n-1] = '\0';

        if (_string_start_with(buffer, prefix, prefix_size)) {
            first_time = wobj_false;
            char* tokens[4]; //esempio: v 0.1 -0.5 0.9\n
            _string_split(buffer, " ", tokens);
            out_vertices[count++] = atof(tokens[1]);
            out_vertices[count++] = atof(tokens[2]);
            out_vertices[count++] = atof(tokens[3]); // lo '\n' lo rimuove atof. Non gli da fastidio
        } else if (!_string_start_with(buffer, prefix, prefix_size) && !first_time) {
            int n_read = strlen(buffer) + 1;
            fseek(file, -n_read, SEEK_CUR);
            return;
        }
    }
}

static void _wobj_parse_uvs(FILE* file, float* out_uvs) {
    char prefix[] = "vt ";
    int prefix_size = 3;
    char buffer[1024]; 
    wobj_bool first_time = wobj_true;
    int count = 0;
    while(fgets(buffer, sizeof(buffer), file)) {
        int n = strlen(buffer);
        if (n == 0) continue;
        //if (n == 0 || buffer[n - 1] != '\n') continue;
        //buffer[n-1] = '\0';

        if (_string_start_with(buffer, prefix, prefix_size)) {
            first_time = wobj_false;
            char* tokens[3]; //esempio: vt 0.1 -0.5\n
            _string_split(buffer, " ", tokens);
            out_uvs[count++] = atof(tokens[1]);
            out_uvs[count++] = atof(tokens[2]); // lo '\n' lo rimuove atof. Non gli da fastidio
        } else if (!_string_start_with(buffer, prefix, prefix_size) && !first_time) {
            int n_read = strlen(buffer) + 1;
            fseek(file, -n_read, SEEK_CUR);
            return;
        }
    }
}

static void _wobj_parse_normals(FILE* file, float* out_normals) {
    char prefix[] = "vn ";
    int prefix_size = 3;
    char buffer[1024]; 
    wobj_bool first_time = wobj_true;
    int count = 0;
    while(fgets(buffer, sizeof(buffer), file)) {
        int n = strlen(buffer);
        if (n == 0) continue;
        //if (n == 0 || buffer[n - 1] != '\n') continue;
        //buffer[n-1] = '\0';

        if (_string_start_with(buffer, prefix, prefix_size)) {
            first_time = wobj_false;
            char* tokens[4]; //esempio: vn 0.1 -0.5 0.9\n
            _string_split(buffer, " ", tokens);
            out_normals[count++] = atof(tokens[1]);
            out_normals[count++] = atof(tokens[2]);
            out_normals[count++] = atof(tokens[3]); // lo '\n' lo rimuove atof. Non gli da fastidio
        } else if (!_string_start_with(buffer, prefix, prefix_size) && !first_time) {
            int n_read = strlen(buffer) + 1;
            fseek(file, -n_read, SEEK_CUR);
            return;
        }
    }
}

static void _wobj_parse_faces(FILE* file, int* out_faces) {
    char prefix[] = "f ";
    int prefix_size = 2;
    char buffer[1024]; 
    wobj_bool first_time = wobj_true;
    int count = 0;
    while(fgets(buffer, sizeof(buffer), file)) {
        int n = strlen(buffer);
        if (n == 0) continue;
        //if (n == 0 || buffer[n - 1] != '\n') continue;
        //buffer[n-1] = '\0';
    
        if (_string_start_with(buffer, prefix, prefix_size)) {
            first_time = wobj_false;
            //Example: f 1/2/3 4/5/6 7/8/9
            //   where: v-i/vn-i/vt-i 
            //   note: faces indexes are 1-based
            //         so, index-1 is stored to simply array access for later use.
            char* tokens[4];
            _string_split(buffer,    " ", tokens);
            char* group1[3];
            _string_split(tokens[1], "/", group1);
            char* group2[3];
            _string_split(tokens[2], "/", group2);
            char* group3[3];
            _string_split(tokens[3], "/", group3);
            out_faces[count++] = atoi(group1[0]) - 1;
            out_faces[count++] = atoi(group1[1]) - 1;
            out_faces[count++] = atoi(group1[2]) - 1;
            out_faces[count++] = atoi(group2[0]) - 1;
            out_faces[count++] = atoi(group2[1]) - 1;
            out_faces[count++] = atoi(group2[2]) - 1;
            out_faces[count++] = atoi(group3[0]) - 1;
            out_faces[count++] = atoi(group3[1]) - 1;
            out_faces[count++] = atoi(group3[2]) - 1;
        } else if (!_string_start_with(buffer, prefix, prefix_size) && !first_time) {
            int n_read = strlen(buffer) + 1;
            fseek(file, -n_read, SEEK_CUR);
            return;
        }
    }
}

static void wobj_print_stats(wobj* obj) {
    printf("Vertices count: %d\n", obj->vertices_count);
    printf(" Normals count: %d\n", obj->normals_count);
    printf("     Uvs count: %d\n", obj->uvs_count);
    printf("   Faces count: %d\n", obj->faces_count);
}

static wobj* wobj_from_file(const char* file_path) {
    FILE *file = fopen ( file_path, "r" );
    if(file == NULL) { fprintf(stderr, "Error opening file [%s]\n", file_path); return NULL; }

    wobj* obj = (wobj*)malloc(sizeof(wobj));

    //Reading in order, following obj format: v, vt, vn, f
    //This way no need to re-open file or rewind file cursor
    obj->vertices_count = _wobj_count_starting_with(file, "v ", 2);
    obj->vertices_size = obj->vertices_count * 3;

    obj->uvs_count = _wobj_count_starting_with(file, "vt ", 3);
    obj->uvs_size = obj->uvs_count * 2;
    
    obj->normals_count = _wobj_count_starting_with(file, "vn ", 3);
    obj->normals_size = obj->normals_count * 3;

    obj->faces_count = _wobj_count_starting_with(file, "f ", 2);
    obj->faces_size = obj->faces_count * 9;
    
    obj->vertices = malloc(sizeof(float) * obj->vertices_size);
    obj->normals = malloc(sizeof(float) * obj->normals_size);
    obj->uvs = malloc(sizeof(float) * obj->uvs_size);
    obj->faces = malloc(sizeof(int) * obj->faces_size);

    rewind(file); // reset file cursor
    //NOTE: Data reading can be optimized, previously storing start/end index for each component
    _wobj_parse_vertices(file, obj->vertices);
    _wobj_parse_uvs(file, obj->uvs);
    _wobj_parse_normals(file, obj->normals);
    _wobj_parse_faces(file, obj->faces);
    fclose(file);

    obj->triangles_count = obj->faces_count;
    obj->triangles = malloc(sizeof(wobj_triangle) * obj->triangles_count);
    for (size_t i = 0; i < obj->faces_size; i+=9) {
        wobj_triangle t;

        int vertex_index, norm_index, uv_index;

        //Vertex1
        vertex_index = obj->faces[i+0] * 3;
        t.v1.position.x = obj->vertices[vertex_index + 0];
        t.v1.position.y = obj->vertices[vertex_index + 1];
        t.v1.position.z = obj->vertices[vertex_index + 2];
        
        uv_index = obj->faces[i+1] * 2;
        t.v1.uv.x = obj->uvs[uv_index + 0];
        t.v1.uv.y = obj->uvs[uv_index + 1];
        
        norm_index = obj->faces[i+2] * 3;
        t.v1.normal.x = obj->normals[norm_index + 0];
        t.v1.normal.y = obj->normals[norm_index + 1];
        t.v1.normal.z = obj->normals[norm_index + 2];

        //Vertex2
        vertex_index = obj->faces[i+3] * 3;
        t.v2.position.x = obj->vertices[vertex_index + 0];
        t.v2.position.y = obj->vertices[vertex_index + 1];
        t.v2.position.z = obj->vertices[vertex_index + 2];

        uv_index = obj->faces[i+4] * 2;
        t.v2.uv.x = obj->uvs[uv_index + 0];
        t.v2.uv.y = obj->uvs[uv_index + 1];
        
        norm_index = obj->faces[i+5] * 3;
        t.v2.normal.x = obj->normals[norm_index + 0];
        t.v2.normal.y = obj->normals[norm_index + 1];
        t.v2.normal.z = obj->normals[norm_index + 2];

        //Vertex3
        vertex_index = obj->faces[i+6] * 3;
        t.v3.position.x = obj->vertices[vertex_index + 0];
        t.v3.position.y = obj->vertices[vertex_index + 1];
        t.v3.position.z = obj->vertices[vertex_index + 2];

        uv_index = obj->faces[i+7] * 2;
        t.v3.uv.x = obj->uvs[uv_index + 0];
        t.v3.uv.y = obj->uvs[uv_index + 1];

        norm_index = obj->faces[i+8] * 3;
        t.v3.normal.x = obj->normals[norm_index + 0];
        t.v3.normal.y = obj->normals[norm_index + 1];
        t.v3.normal.z = obj->normals[norm_index + 2];

        obj->triangles[i / 9] = t;
    }

    return obj;
}

static void wobj_destroy(wobj* obj) {
    free(obj->vertices);
    free(obj->normals);
    free(obj->uvs);
    free(obj->faces);
    free(obj->triangles);
    free(obj);
}