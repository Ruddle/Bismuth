#include "Vao.h"

using namespace std;
using namespace glm;

Vao::Vao(std::string path) :mPath(path), mVaoID(0), mVboVertexID(0),
mPosition(0), mUv(0), mNormal(0), mTangent(0),mBitangent(0)
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

void Vao::load() {
	load(vec4(1, 0, 1,0.5));
}

void Vao::load(vec4 color)
{
	//mVboInstance
	glGenBuffers(1, &mVboInstanceID);
	glBindBuffer(GL_ARRAY_BUFFER, mVboInstanceID);
	glBufferData(GL_ARRAY_BUFFER, 1 * (sizeof(vec4)), 0, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 1*sizeof(vec4), &color[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//mVboVertex
	glGenBuffers(1, &mVboVertexID);
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertexID);
	glBufferData(GL_ARRAY_BUFFER, mPosition.size()*(sizeof(vec3) * 4 + sizeof(vec2)), 0, GL_STATIC_DRAW);  // Position + normal + uv
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3)*mPosition.size(), &mPosition[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3)*mPosition.size(), sizeof(vec3)*mNormal.size(), &mNormal[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 2 * sizeof(vec3)*mPosition.size(), sizeof(vec2)*mUv.size(), &mUv[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 2 * sizeof(vec3)*mPosition.size()+ sizeof(vec2)*mUv.size(), sizeof(vec3)*mPosition.size(), &mTangent[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(vec3)*mPosition.size() + sizeof(vec2)*mUv.size(), sizeof(vec3)*mPosition.size(), &mBitangent[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//mVao
	glGenVertexArrays(1, &mVaoID);
	glBindVertexArray(mVaoID);

	//mVboVertex
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertexID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)); //position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec3)*mPosition.size())); //normal
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2 * sizeof(vec3)*mPosition.size())); // uv
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2 * sizeof(vec3)*mPosition.size() + sizeof(vec2)*mUv.size())); // uv
	glEnableVertexAttribArray(4);

	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(3 * sizeof(vec3)*mPosition.size() + sizeof(vec2)*mUv.size())); // uv
	glEnableVertexAttribArray(5);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//mVboInstance
	glBindBuffer(GL_ARRAY_BUFFER, mVboInstanceID);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)); 
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1);

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
	vector<vec3> position;
	vector<vec3> normal;
	vector<vec2> uv;

	vector<int> indexPosition;
	vector<int> indexNormal;
	vector<int> indexUv;

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
			position.push_back(vec3(0));
			lineStream >> position.back().x;
			lineStream >> position.back().y;
			lineStream >> position.back().z;
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
				indexPosition.push_back(num);

				it >> num;
				indexUv.push_back(num);

				in >> num;
				indexNormal.push_back(num);
			}
		}
	}
	flux.close();

	for (int i = 0; i < indexPosition.size(); i++)
	{
		int index = indexNormal[i] - 1;
		mNormal.push_back(normal[index]);

		index = indexPosition[i] - 1;
		mPosition.push_back(position[index]);
	}

	for (int k = 0; k <indexPosition.size(); k++)
	{
		int index = indexUv[k] - 1;
		mUv.push_back(uv[index]);
	}

/*	cout << "numVertex : " << indexPosition.size() << endl;
	for (int i = 0; i < indexPosition.size() * 1; i++)
	{
		cout << "n : " << i << endl;
		cout << "Position " << " x : " << mPosition[i].x << " y : " << mPosition[i].y << " z : " << mPosition[i].z << endl;
		cout << "Normal " << " x : " << mNormal[i].x << " y : " << mNormal[i].y << " z : " << mNormal[i].z << endl;
		cout << "UV     " << " x : " << mUv[i].x << " y : " << mUv[i].y << endl;
	}*/



	for (int i = 0; i < mNormal.size(); i+=3)
	{
		// Shortcuts for vertices
		glm::vec3 & v0 = mPosition[i + 0];
		glm::vec3 & v1 = mPosition[i + 1];
		glm::vec3 & v2 = mPosition[i + 2];

		// Shortcuts for UVs
		glm::vec2 & uv0 = mUv[i + 0];
		glm::vec2 & uv1 = mUv[i + 1];
		glm::vec2 & uv2 = mUv[i + 2];

		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;

		// UV delta
		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;


		mTangent.push_back(tangent);
		mTangent.push_back(tangent);
		mTangent.push_back(tangent);

		
		mBitangent.push_back(bitangent);
		mBitangent.push_back(bitangent);
		mBitangent.push_back(bitangent);

	}










}