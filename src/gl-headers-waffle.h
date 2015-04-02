/*
 * Copyright 2015 Google Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */
#ifndef GL_HEADERS_WAFFLE_H_
#define GL_HEADERS_WAFFLE_H_

#include <KHR/khrplatform.h>

namespace hide_gles2 {
// Can't use the function declarations in this header because we need to
// declare them as pointers to be looked up with waffle, so hide them in
// this namespace.
// This way we still get all the #defines in the header.
#include <GLES2/gl2.h>
};

// Unfortunately now these types are hidden and need to be exposed.
using hide_gles2::GLbyte;
using hide_gles2::GLclampf;
using hide_gles2::GLfixed;
using hide_gles2::GLshort;
using hide_gles2::GLushort;
using hide_gles2::GLvoid;
using hide_gles2::GLsync;
using hide_gles2::GLint64;
using hide_gles2::GLuint64;
using hide_gles2::GLenum;
using hide_gles2::GLuint;
using hide_gles2::GLchar;
using hide_gles2::GLfloat;
using hide_gles2::GLsizeiptr;
using hide_gles2::GLintptr;
using hide_gles2::GLbitfield;
using hide_gles2::GLint;
using hide_gles2::GLboolean;
using hide_gles2::GLsizei;
using hide_gles2::GLubyte;

#define GLES2_FUNCTION_LIST(f) \
f(void           , glActiveTexture           , (GLenum texture)) \
f(void           , glAttachShader            , (GLuint program, GLuint shader)) \
f(void           , glBindBuffer              , (GLenum target, GLuint buffer)) \
f(void           , glBindFramebuffer         , (GLenum target, GLuint framebuffer)) \
f(void           , glBindRenderbuffer        , (GLenum target, GLuint renderbuffer)) \
f(void           , glBindTexture             , (GLenum target, GLuint texture)) \
f(void           , glBlendFunc               , (GLenum sfactor, GLenum dfactor)) \
f(void           , glBlendFuncSeparate       , (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)) \
f(void           , glBufferData              , (GLenum target, GLsizeiptr size, const void *data, GLenum usage)) \
f(void           , glBufferSubData           , (GLenum target, GLintptr offset, GLsizeiptr size, const void *data)) \
f(GLenum         , glCheckFramebufferStatus  , (GLenum target)) \
f(void           , glClearColor              , (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)) \
f(void           , glClearDepthf             , (GLfloat d)) \
f(void           , glClear                   , (GLbitfield mask)) \
f(void           , glColorMask               , (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)) \
f(void           , glCompileShader           , (GLuint shader)) \
f(GLuint         , glCreateProgram           , (void)) \
f(GLuint         , glCreateShader            , (GLenum type)) \
f(void           , glCullFace                , (GLenum mode)) \
f(void           , glDeleteBuffers           , (GLsizei n, const GLuint *buffers)) \
f(void           , glDeleteFramebuffers      , (GLsizei n, const GLuint *framebuffers)) \
f(void           , glDeleteProgram           , (GLuint program)) \
f(void           , glDeleteRenderbuffers     , (GLsizei n, const GLuint *renderbuffers)) \
f(void           , glDeleteShader            , (GLuint shader)) \
f(void           , glDeleteTextures          , (GLsizei n, const GLuint *textures)) \
f(void           , glDepthFunc               , (GLenum func)) \
f(void           , glDepthMask               , (GLboolean flag)) \
f(void           , glDisable                 , (GLenum cap)) \
f(void           , glDisableVertexAttribArray, (GLuint index)) \
f(void           , glDrawArrays              , (GLenum mode, GLint first, GLsizei count)) \
f(void           , glDrawElements            , (GLenum mode, GLsizei count, GLenum type, const void *indices)) \
f(void           , glEnable                  , (GLenum cap)) \
f(void           , glEnableVertexAttribArray , (GLuint index)) \
f(void           , glFinish                  , (void)) \
f(void           , glFramebufferRenderbuffer , (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)) \
f(void           , glFramebufferTexture2D    , (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)) \
f(void           , glGenBuffers              , (GLsizei n, GLuint *buffers)) \
f(void           , glGenerateMipmap          , (GLenum target)) \
f(void           , glGenFramebuffers         , (GLsizei n, GLuint *framebuffers)) \
f(void           , glGenRenderbuffers        , (GLsizei n, GLuint *renderbuffers)) \
f(void           , glGenTextures             , (GLsizei n, GLuint *textures)) \
f(GLint          , glGetAttribLocation       , (GLuint program, const GLchar *name)) \
f(void           , glGetBooleanv             , (GLenum pname, GLboolean *data)) \
f(GLenum         , glGetError                , (void)) \
f(void           , glGetIntegerv             , (GLenum pname, GLint *data)) \
f(void           , glGetProgramInfoLog       , (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)) \
f(void           , glGetProgramiv            , (GLuint program, GLenum pname, GLint *params)) \
f(void           , glGetShaderInfoLog        , (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)) \
f(void           , glGetShaderiv             , (GLuint shader, GLenum pname, GLint *params)) \
f(const GLubyte *, glGetString               , (GLenum name)) \
f(GLint          , glGetUniformLocation      , (GLuint program, const GLchar *name)) \
f(GLboolean      , glIsEnabled               , (GLenum cap)) \
f(void           , glLinkProgram             , (GLuint program)) \
f(void           , glReadPixels              , (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels)) \
f(void           , glRenderbufferStorage     , (GLenum target, GLenum internalformat, GLsizei width, GLsizei height)) \
f(void           , glShaderSource            , (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length)) \
f(void           , glTexImage2D              , (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)) \
f(void           , glTexParameteri           , (GLenum target, GLenum pname, GLint param)) \
f(void           , glUniform1f               , (GLint location, GLfloat v0)) \
f(void           , glUniform1i               , (GLint location, GLint v0)) \
f(void           , glUniform2fv              , (GLint location, GLsizei count, const GLfloat *value)) \
f(void           , glUniform3fv              , (GLint location, GLsizei count, const GLfloat *value)) \
f(void           , glUniform4fv              , (GLint location, GLsizei count, const GLfloat *value)) \
f(void           , glUniformMatrix3fv        , (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)) \
f(void           , glUniformMatrix4fv        , (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)) \
f(void           , glUseProgram              , (GLuint program)) \
f(void           , glVertexAttribPointer     , (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)) \
f(void           , glViewport                , (GLint x, GLint y, GLsizei width, GLsizei height)) \


#define DECLARE(type, func, args) extern type (*func) args;
GLES2_FUNCTION_LIST(DECLARE)
#undef DECLARE

#endif // GL_HEADERS_WAFFLE_H_
