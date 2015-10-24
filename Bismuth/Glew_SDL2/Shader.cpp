#include "Shader.h"
#include <fstream>
#include <string>

// Constructeurs et Destructeur

Shader::Shader() : mVertexID(0), mFragmentID(0), mProgramID(0), mVertexSource(), mFragmentSource()
{
}


Shader::Shader(Shader const &shaderACopier)
{
	// Copie des fichiers sources

	mVertexSource = shaderACopier.mVertexSource;
	mFragmentSource = shaderACopier.mFragmentSource;


	// Chargement du nouveau shader

	load();
}


Shader::Shader(std::string vertexSource, std::string fragmentSource) : mVertexID(0), mFragmentID(0), mProgramID(0),
mVertexSource(vertexSource), mFragmentSource(fragmentSource)
{
}


Shader::~Shader()
{
	// Destruction du shader

	glDeleteShader(mVertexID);
	glDeleteShader(mFragmentID);
	glDeleteProgram(mProgramID);
}


// Méthodes

Shader& Shader::operator=(Shader const &shaderACopier)
{
	// Copie des fichiers sources

	mVertexSource = shaderACopier.mVertexSource;
	mFragmentSource = shaderACopier.mFragmentSource;


	// Chargement du nouveau shader

	load();


	// Retour du pointeur this

	return *this;
}


bool Shader::load()
{
	// Destruction d'un éventuel ancien Shader

	if (glIsShader(mVertexID) == GL_TRUE)
		glDeleteShader(mVertexID);

	if (glIsShader(mFragmentID) == GL_TRUE)
		glDeleteShader(mFragmentID);

	if (glIsProgram(mProgramID) == GL_TRUE)
		glDeleteProgram(mProgramID);


	// Compilation des shaders

	if (!compileShader(mVertexID, GL_VERTEX_SHADER, mVertexSource))
		return false;

	if (!compileShader(mFragmentID, GL_FRAGMENT_SHADER, mFragmentSource))
		return false;


	// Création du programme

	mProgramID = glCreateProgram();


	// Association des shaders

	glAttachShader(mProgramID, mVertexID);
	glAttachShader(mProgramID, mFragmentID);


	// Verrouillage des entrées shader

	glBindAttribLocation(mProgramID, 0, "inPosition");
	glBindAttribLocation(mProgramID, 1, "inNormal");
	glBindAttribLocation(mProgramID, 2, "inColor");
	glBindAttribLocation(mProgramID, 3, "inUV");


	// Linkage du programme

	glLinkProgram(mProgramID);


	// Vérification du linkage

	GLint erreurLink(0);
	glGetProgramiv(mProgramID, GL_LINK_STATUS, &erreurLink);


	// S'il y a eu une erreur

	if (erreurLink != GL_TRUE)
	{
		// Récupération de la de l'erreur

		GLint errorSize(0);
		glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &errorSize);


		// Allocation de mémoire

		char *error = new char[errorSize + 1];


		// Récupération de l'erreur

		glGetShaderInfoLog(mProgramID, errorSize, &errorSize, error);
		error[errorSize] = '\0';


		// Affichage de l'erreur

		std::cout << error << std::endl;


		// Libération de la mémoire et retour du booléen false

		delete[] error;
		glDeleteProgram(mProgramID);

		return false;
	}



	// Sinon c'est que tout s'est bien passé

	else
		return true;
}


bool Shader::compileShader(GLuint &shader, GLenum type, std::string const &sourceFile)
{
	// Création du shader

	shader = glCreateShader(type);


	// Vérification du shader

	if (shader == 0)
	{
		std::cout << "Error, shader type (" << type << ") does not exist" << std::endl;
		return false;
	}


	// Flux de lecture

	std::ifstream file(sourceFile.c_str());


	// Test d'ouverture

	if (!file)
	{
		std::cout << "Error, file " << sourceFile << " not found" << std::endl;
		glDeleteShader(shader);

		return false;
	}


	// Strings permettant de lire le code source

	std::string line;
	std::string sourceCode;


	// Lecture

	while (getline(file, line))
		sourceCode += line + '\n';


	// Fermeture du fichier

	file.close();


	// Récupération de la chaine C du code source

	const GLchar* sourceCodeString = sourceCode.c_str();


	// Envoi du code source au shader

	glShaderSource(shader, 1, &sourceCodeString, 0);


	// Compilation du shader

	glCompileShader(shader);


	// Vérification de la compilation

	GLint compilationError(0);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationError);


	// S'il y a eu une erreur

	if (compilationError != GL_TRUE)
	{
		// Récupération de la taille de l'erreur

		GLint errorSize(0);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorSize);


		// Allocation de mémoire

		char *error = new char[errorSize + 1];


		// Récupération de l'erreur

		glGetShaderInfoLog(shader, errorSize, &errorSize, error);
		error[errorSize] = '\0';


		// Affichage de l'erreur

		std::cout << error << std::endl;


		// Libération de la mémoire et retour du booléen false

		delete[] error;
		glDeleteShader(shader);

		return false;
	}


	// Sinon c'est que tout s'est bien passé

	else
		return true;
}


// Getter

GLuint Shader::getProgramID() const
{
	return mProgramID;
}
