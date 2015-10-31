#include "Vao2D.h"


Vao2D::Vao2D() :
	mVboId(0), mVaoId(0)
{




}


Vao2D::~Vao2D()
{
	// Destruction du VBO
	glDeleteBuffers(1, &mVboId);


	// Destruction du VAO
	glDeleteVertexArrays(1, &mVaoId);


}


void Vao2D::load()
{
	//LOAD VBO
	// Destruction d'un �ventuel ancien VBO

	if (glIsBuffer(mVboId) == GL_TRUE)
		glDeleteBuffers(1, &mVboId);

	// G�n�ration de l'ID
	glGenBuffers(1, &mVboId);

	// Verrouillage du VBO
	glBindBuffer(GL_ARRAY_BUFFER, mVboId);


	// Allocation de la m�moire vid�o
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float) + 6 * 2 * sizeof(float), 0, GL_STATIC_DRAW);

	// Transfert des donn�es
	

	float m_vertex[18] = {
		0,0,0,
		1,0,0,
		1,1,0,

		0,0,0,
		1,1,0,
		0,1,0
	};

	for (int i = 0; i < 18; i++)
	{
		if (i % 3 == 2)
			i++;

		m_vertex[i] -= 0.5;
	}


	for (int i = 0; i < 18; i++)
	m_vertex[i] *= 2;

	float m_coords[12] = {
		0, 0,
		1, 0,
		1, 1,

		0, 0,
		1, 1,
		0, 1,
	};

	glBufferSubData(GL_ARRAY_BUFFER, 0, 18 * sizeof(float), m_vertex);
	glBufferSubData(GL_ARRAY_BUFFER, 18 * sizeof(float), 12 * sizeof(float), m_coords);


	// D�verrouillage de l'objet

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//VBO LOADED

	//LOAD VAO
	// Destruction d'un �ventuel ancien VAO

	if (glIsVertexArray(mVaoId) == GL_TRUE)
		glDeleteVertexArrays(1, &mVaoId);


	// G�n�ration de l'identifiant du VAO

	glGenVertexArrays(1, &mVaoId);


	// Verrouillage du VAO

	glBindVertexArray(mVaoId);


	// Verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, mVboId);


	// Acc�s aux vertices dans la m�moire vid�o

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);


	// Acc�s aux couleurs dans la m�moire vid�o

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(18 * sizeof(float)));
	glEnableVertexAttribArray(3);




	// D�verrouillage du VBO

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// D�verrouillage du VAO

	glBindVertexArray(0);
	//VAO LOADED
}




void Vao2D::draw()
{
	// Verrouillage du VAO

	glBindVertexArray(mVaoId);

	// Rendu

	glDrawArrays(GL_TRIANGLES, 0, 18 / 3);

	// D�verrouillage du VAO

	glBindVertexArray(0);
}