#ifndef RENDERCOMMANDS_H_
#define RENDERCOMMANDS_H_

#include <glad/glad.h>
#include <VertexArray.h>
#include <glm/vec3.hpp>

namespace RenderCommands
{
	inline void Clear(GLuint mode = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) { glClear(mode); }
	inline void SetPolygonMode(GLenum face, GLenum mode) { glPolygonMode(face, mode); }
	inline void DrawIndex(const std::shared_ptr<VertexArray>& vao, GLenum primitive, GLsizei count = 0, int start = 0) {
		if(count) glDrawElements(primitive, count, GL_UNSIGNED_INT, (void*)(start * sizeof(GLuint)));
		else glDrawElements(primitive, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	inline void SetClearColor(glm::vec3 rgb) { glClearColor(rgb[0], rgb[1], rgb[2], 1.0f); }
	inline void SetWireFrameMode() { SetPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
	inline void SetSolidMode() { SetPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
}


#endif