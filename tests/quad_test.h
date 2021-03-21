#include "clove.h"
#include "wobj.h"

CLOVE_TEST(test_quad_vertices) {
    wobj* obj = wobj_from_file("resources/quad.obj");

    CLOVE_INT_EQ(4, obj->vertices_count);
    CLOVE_INT_EQ(12, obj->vertices_size);
    
    //v1 
    CLOVE_FLOAT_EQ(-1.f, obj->vertices[0]);
    CLOVE_FLOAT_EQ(1.f, obj->vertices[1]);
    CLOVE_FLOAT_EQ(0.f, obj->vertices[2]);
    //v2
    CLOVE_FLOAT_EQ(1.f, obj->vertices[3]);
    CLOVE_FLOAT_EQ(1.f, obj->vertices[4]);
    CLOVE_FLOAT_EQ(0.f, obj->vertices[5]);
    //v3
    CLOVE_FLOAT_EQ(-1.f, obj->vertices[6]);
    CLOVE_FLOAT_EQ(-1.f, obj->vertices[7]);
    CLOVE_FLOAT_EQ(0.f, obj->vertices[8]);
    //v4
    CLOVE_FLOAT_EQ(1.f, obj->vertices[9]);
    CLOVE_FLOAT_EQ(-1.f, obj->vertices[10]);
    CLOVE_FLOAT_EQ(0.f, obj->vertices[11]);

    wobj_destroy(obj);
}

CLOVE_TEST(test_quad_faces) {
    wobj* obj = wobj_from_file("resources/quad.obj");

    CLOVE_INT_EQ(2, obj->faces_count);
    CLOVE_INT_EQ(18, obj->faces_size);
    
    //f1 
    CLOVE_INT_EQ(3, obj->faces[0]);
    CLOVE_INT_EQ(3, obj->faces[1]);
    CLOVE_INT_EQ(0, obj->faces[2]);
    CLOVE_INT_EQ(2, obj->faces[3]);
    CLOVE_INT_EQ(2, obj->faces[4]);
    CLOVE_INT_EQ(0, obj->faces[5]);
    CLOVE_INT_EQ(0, obj->faces[6]);
    CLOVE_INT_EQ(1, obj->faces[7]);
    CLOVE_INT_EQ(0, obj->faces[8]);

    //f2
    CLOVE_INT_EQ(1, obj->faces[9]);
    CLOVE_INT_EQ(0, obj->faces[10]);
    CLOVE_INT_EQ(0, obj->faces[11]);
    CLOVE_INT_EQ(3, obj->faces[12]);
    CLOVE_INT_EQ(3, obj->faces[13]);
    CLOVE_INT_EQ(0, obj->faces[14]);
    CLOVE_INT_EQ(0, obj->faces[15]);
    CLOVE_INT_EQ(1, obj->faces[16]);
    CLOVE_INT_EQ(0, obj->faces[17]);
    
    wobj_destroy(obj);
}

CLOVE_TEST(test_quad_uvs) {
    wobj* obj = wobj_from_file("resources/quad.obj");

    CLOVE_INT_EQ(4, obj->uvs_count);
    CLOVE_INT_EQ(8, obj->uvs_size);
    
    //vt1 
    CLOVE_FLOAT_EQ(1.f, obj->uvs[0]);
    CLOVE_FLOAT_EQ(1.f, obj->uvs[1]);
    //vt2
    CLOVE_FLOAT_EQ(0.f, obj->uvs[2]);
    CLOVE_FLOAT_EQ(1.f, obj->uvs[3]);
    //vt3
    CLOVE_FLOAT_EQ(0.f, obj->uvs[4]);
    CLOVE_FLOAT_EQ(0.f, obj->uvs[5]);
    //vt4
    CLOVE_FLOAT_EQ(1.f, obj->uvs[6]);
    CLOVE_FLOAT_EQ(0.f, obj->uvs[7]);

    wobj_destroy(obj);
}


CLOVE_TEST(test_quad_triangles) {
    wobj* obj = wobj_from_file("resources/quad.obj");

    CLOVE_INT_EQ(2, obj->triangles_count);
    
    wobj_triangle* t1 = &obj->triangles[0];
    //T1: Positions
    CLOVE_FLOAT_EQ(1.f, t1->v1.position.x);
    CLOVE_FLOAT_EQ(-1.f,  t1->v1.position.y);
    CLOVE_FLOAT_EQ(0.f,  t1->v1.position.z);
    CLOVE_FLOAT_EQ(-1.f,  t1->v2.position.x);
    CLOVE_FLOAT_EQ(-1.f,  t1->v2.position.y);
    CLOVE_FLOAT_EQ(0.f,  t1->v2.position.z);
    CLOVE_FLOAT_EQ(-1.f, t1->v3.position.x);
    CLOVE_FLOAT_EQ(1.f, t1->v3.position.y);
    CLOVE_FLOAT_EQ(0.f,  t1->v3.position.z);

    //T1: Uvs
    CLOVE_FLOAT_EQ(1.f, t1->v1.uv.x);
    CLOVE_FLOAT_EQ(0.f,  t1->v1.uv.y);
    CLOVE_FLOAT_EQ(0.f,  t1->v2.uv.x);
    CLOVE_FLOAT_EQ(0.f,  t1->v2.uv.y);
    CLOVE_FLOAT_EQ(0.f, t1->v3.uv.x);
    CLOVE_FLOAT_EQ(1.f, t1->v3.uv.y);

    //T1: Normals
    CLOVE_FLOAT_EQ(0.f,  t1->v1.normal.x);
    CLOVE_FLOAT_EQ(0.f,  t1->v1.normal.y);
    CLOVE_FLOAT_EQ(1.f,  t1->v1.normal.z);
    CLOVE_FLOAT_EQ(0.f,  t1->v2.normal.x);
    CLOVE_FLOAT_EQ(0.f,  t1->v2.normal.y);
    CLOVE_FLOAT_EQ(1.f,  t1->v2.normal.z);
    CLOVE_FLOAT_EQ(0.f,  t1->v3.normal.x);
    CLOVE_FLOAT_EQ(0.f,  t1->v3.normal.y);
    CLOVE_FLOAT_EQ(1.f,  t1->v3.normal.z);


    wobj_triangle* t2 = &obj->triangles[1];
    //T2: Positions
    CLOVE_FLOAT_EQ(1.f, t2->v1.position.x);
    CLOVE_FLOAT_EQ(1.f,  t2->v1.position.y);
    CLOVE_FLOAT_EQ(0.f,  t2->v1.position.z);
    CLOVE_FLOAT_EQ(1.f,  t2->v2.position.x);
    CLOVE_FLOAT_EQ(-1.f,  t2->v2.position.y);
    CLOVE_FLOAT_EQ(0.f,  t2->v2.position.z);
    CLOVE_FLOAT_EQ(-1.f, t2->v3.position.x);
    CLOVE_FLOAT_EQ(1.f, t2->v3.position.y);
    CLOVE_FLOAT_EQ(0.f,  t2->v3.position.z);

    //T2: Uvs
    CLOVE_FLOAT_EQ(1.f, t2->v1.uv.x);
    CLOVE_FLOAT_EQ(1.f,  t2->v1.uv.y);
    CLOVE_FLOAT_EQ(1.f,  t2->v2.uv.x);
    CLOVE_FLOAT_EQ(0.f,  t2->v2.uv.y);
    CLOVE_FLOAT_EQ(0.f, t2->v3.uv.x);
    CLOVE_FLOAT_EQ(1.f, t2->v3.uv.y);

    //T2: Normals
    CLOVE_FLOAT_EQ(0.f,  t1->v1.normal.x);
    CLOVE_FLOAT_EQ(0.f,  t1->v1.normal.y);
    CLOVE_FLOAT_EQ(1.f,  t1->v1.normal.z);
    CLOVE_FLOAT_EQ(0.f,  t1->v2.normal.x);
    CLOVE_FLOAT_EQ(0.f,  t1->v2.normal.y);
    CLOVE_FLOAT_EQ(1.f,  t1->v2.normal.z);
    CLOVE_FLOAT_EQ(0.f,  t1->v3.normal.x);
    CLOVE_FLOAT_EQ(0.f,  t1->v3.normal.y);
    CLOVE_FLOAT_EQ(1.f,  t1->v3.normal.z);

    wobj_destroy(obj);
}


