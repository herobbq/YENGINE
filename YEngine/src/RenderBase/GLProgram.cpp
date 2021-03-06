#include "GLProgram.h"

const int GLProgram::LAYOUT_INDEX_POSITION = 0;

const int GLProgram::LAYOUT_INDEX_NORMAL = 1;

const int GLProgram::LAYOUT_INDEX_TEXCOORDS = 2;

const int GLProgram::LAYOUT_INDEX_TANGENT = 3;

const int GLProgram::LAYOUT_INDEX_BITTANGENT = 4;

const char* GLProgram::UNIFORM_NAME_MODEL = "u_model";

const char* GLProgram::UNIFORM_NAME_VIEW = "u_view";

const char* GLProgram::UNIFORM_NAME_PROJECTION  = "u_projection";

const char* GLProgram::UNIFORM_NAME_TEXTURE1 = "u_texture1";

const char* GLProgram::UNIFORM_NAME_TEXTURE2 = "u_texture2";

const char* GLProgram::UNIFORM_NAME_CUBETEXTURE = "u_cubetexture";

const char* GLProgram::UNIFORM_NAME_VIEWPOS = "u_viewPos";

// Attribute names
const char* GLProgram::ATTRIBUTE_NAME_COLOR = "a_color";
const char* GLProgram::ATTRIBUTE_NAME_POSITION = "a_position";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD = "a_texCoord";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD1 = "a_texCoord1";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD2 = "a_texCoord2";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD3 = "a_texCoord3";
const char* GLProgram::ATTRIBUTE_NAME_NORMAL = "a_normal";
const char* GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT = "a_blendWeight";
const char* GLProgram::ATTRIBUTE_NAME_BLEND_INDEX = "a_blendIndex";
const char* GLProgram::ATTRIBUTE_NAME_TANGENT = "a_tangent";
const char* GLProgram::ATTRIBUTE_NAME_BINORMAL = "a_binormal";

