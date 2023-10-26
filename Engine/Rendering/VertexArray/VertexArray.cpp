#include <iostream>

#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_vertexArrayID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void VertexArray::Bind() const {
	glBindVertexArray(m_vertexArrayID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
	Bind();
	
	vertexBuffer->Bind();

	int attribCount = 0;
	for (int i = 0; i < VertexBuffers.size(); ++i) {
		attribCount += VertexBuffers[i]->GetLayout().GetAttributes().size();
	}

	std::vector<BufferAttribute> attribs = vertexBuffer->GetLayout().GetAttributes();
	for (int i = 0; i < attribs.size(); ++i) {
		GLuint index = attribCount++;
		GLint size = ShaderDataTypeComponentCount(attribs[i].Type);
		GLenum type = ShaderDataTypeToOpenGLBaseType(attribs[i].Type);
		GLboolean normalized = attribs[i].Normalized;
		GLsizei stride = vertexBuffer->GetLayout().GetStride();
		const void* pointer = (void*) attribs[i].Offset;

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}
	VertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
	Bind();
	IdxBuffer = indexBuffer;
}