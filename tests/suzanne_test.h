#include "clove.h"
#include "wobj.h"

CLOVE_TEST(test_suzanne_info) {
    wobj* obj = wobj_from_file("resources/suzanne.obj");

    CLOVE_INT_EQ(511, obj->vertices_count);
    CLOVE_INT_EQ(590, obj->uvs_count);
    CLOVE_INT_EQ(507, obj->normals_count);
    CLOVE_INT_EQ(968, obj->faces_count);
    CLOVE_INT_EQ(968, obj->triangles_count);
    
    wobj_destroy(obj);
}
