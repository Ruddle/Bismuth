#include "Vao.h"

using namespace std;
using namespace glm;

Vao::Vao(std::string path) :mPath(path), mVaoID(0), mVboVertexID(0),
mPosition(0), mUv(0), mNormal(0)
{

	loadFile();
}

Vao::~Vao()
{
	// Destruction du VBO
	glDeleteBuffers(1, &mVboVertexID);

	// Destruction du Vao
	glDeleteVertexArrays(1, &mVaoID);

}

void Vao::load()
{
	//mVboVertex
	glGenBuffers(1, &mVboVertexID);
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertexID);
	glBufferData(GL_ARRAY_BUFFER, mPosition.size()*(sizeof(vec3) * 2 + sizeof(vec2)), 0, GL_STATIC_DRAW);  // Position + normal + uv
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3)*mPosition.size(), &mPosition[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3)*mPosition.size(), sizeof(vec3)*mNormal.size(), &mNormal[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 2 * sizeof(vec3)*mPosition.size(), sizeof(vec2)*mUv.size(), &mUv[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//mVao
	glGenVertexArrays(1, &mVaoID);
	glBindVertexArray(mVaoID);

	//mVboVertex
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertexID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)); //position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec3)*mPosition.size())); //normal
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2 * sizeof(vec3)*mPosition.size())); // uv
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);
	//Vao LOADED
}
void Vao::draw()
{
	glBindVertexArray(mVaoID);
	glDrawArrays(GL_TRIANGLES, 0, mPosition.size());
	glBindVertexArray(0);
}


void Vao::loadFile()
{
	vector<vec3> vertex;
	vector<vec3> normal;
	vector<vec2> uv;

	vector<int> indexV;
	vector<int> indexN;
	vector<int> indexT;

	ifstream flux(mPath.c_str());

	if (!flux)
		cout << "ERROR : Loading of " << mPath << " failed !" << endl;


	bool loading = true;
	while (loading)
	{
		string word;
		string line;
		if (!getline(flux, line)) //On lit une ligne complète
			loading = false;

		istringstream lineStream(line);
		lineStream >> word;

		if (word == ("v"))
		{
			vertex.push_back(vec3(0));
			lineStream >> vertex.back().x;
			lineStream >> vertex.back().y;
			lineStream >> vertex.back().z;
		}
		else if (word == ("vt"))
		{
			uv.push_back(vec2(0));
			lineStream >> uv.back().x;
			lineStream >> uv.back().y;
		}
		else if (word == ("vn"))
		{
			normal.push_back(vec3(0));
			lineStream >> normal.back().x;
			lineStream >> normal.back().y;
			lineStream >> normal.back().z;
		}
		else if (word == ("f"))
		{

			for (int i = 0; i < 3; i++)
			{
				string indexVertex;
				lineStream >> indexVertex;

				int slash1 = indexVertex.find("/");
				int slash2 = indexVertex.find("/", slash1 + 1);

				istringstream iv(indexVertex.substr(0, slash1));
				istringstream it(indexVertex.substr(slash1 + 1, slash2 - slash1 - 1));
				istringstream in(indexVertex.substr(slash2 + 1));

				float num;

				iv >> num;
				indexV.push_back(num);

				it >> num;
				indexT.push_back(num);

				in >> num;
				indexN.push_back(num);
			}
		}
	}
	flux.close();

	for (int i = 0; i < indexV.size(); i++)
	{
		int index = indexN[i] - 1;
		mNormal.push_back(normal[index]);

		index = indexV[i] - 1;
		mPosition.push_back(vertex[index]);
	}

	for (int k = 0; k <indexV.size(); k++)
	{
		int index = indexT[k] - 1;
		mUv.push_back(uv[index]);
	}

/*	cout << "numVertex : " << indexV.size() << endl;
	for (int i = 0; i < indexV.size() * 1; i++)
	{
		cout << "n : " << i << endl;
		cout << "Vertex " << " x : " << mPosition[i].x << " y : " << mPosition[i].y << " z : " << mPosition[i].z << endl;
		cout << "Normal " << " x : " << mNormal[i].x << " y : " << mNormal[i].y << " z : " << mNormal[i].z << endl;
		cout << "uv     " << " x : " << mUv[i].x << " y : " << mUv[i].y << endl;
	}*/
}