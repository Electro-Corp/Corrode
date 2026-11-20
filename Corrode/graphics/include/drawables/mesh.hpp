/*
    Project Corrode Graphics Engine (PCGE)
    mesh.hpp - holds and renders mesh data (modified from my other project: https://github.com/Electro-Corp/LARE)
*/
#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <glm/glm.hpp>

#include <common/transform.hpp>
#include <shader.hpp>
#include <drawable.hpp>
#include <camera.hpp>

#define NUM_VERT_DATA 8

namespace Drawable{
    struct Vertex {
		glm::vec3 pos;
		glm::vec2 texCoord;
		glm::vec3 normal;
		//glm::vec3 tangents;
		
		Vertex(glm::vec3 p, glm::vec2 t, glm::vec3 n) : pos(p), texCoord(t), normal(n) {}
    };

    struct Texture {
        unsigned int id;
        std::string type, path;

		Texture(unsigned int i, std::string t, std::string p) : id(i), type(std::move(t)), path(std::move(p)) {}
    };

    class Mesh : public Rendering::Drawable {
	private:
		// Pretty self explanatory, just the ends of our triangle
		std::vector<Vertex> vertices;
		/*
		 * Ooh goody optimization
		 * Often, triangles will share multiple verticies, as shown here in this simple example:
		 *      v0 --------------- v1
		 *     v5 | *              |
		 *        |     *          |
		 *        |         *      |
		 *        |             *  |
		 *      v4 ---------------- v2
		 *                         v3
		 *  So why bother using that many verts when v0 and v5 are the same and v3 and v2 are?
		 *  Yay for index buffers
		 */
        std::vector<std::uint32_t> indices;
        // Textures 
        std::vector<Texture> textures;

		// Shader program
		unsigned int shaderID;
	public:
		// Has our mesh been modified?
		bool modified = false;
        /*
         *  VAO -> Tells OpenGL how our vertices are laid out
         *  VBO -> for our vertices
         *  EBO -> for our indices
         */
        unsigned int VBO, VAO, EBO;

		Mesh(std::vector<Vertex> verts, std::vector<std::uint32_t> inds, std::vector<Texture> textures, std::shared_ptr<Rendering::ShaderProgram> shader);

        void initMesh();

        void draw(const Rendering::Camera& cam) override;
		void draw(const Rendering::Camera& cam, unsigned int overrideShader) override;

		// Getters/Setters
		float* packVerts();

		unsigned int* packInds();

		std::vector<Vertex> getVertices() {
			return vertices;
		}

		void setVertices(std::vector<Vertex> verts) {
			this->vertices = verts;
			modified = true;
		}

		std::vector<std::uint32_t> getIndicies() {
			return indices;
		}

		void setIndicies(std::vector<std::uint32_t> inds) {
			this->indices = inds;
			modified = true;
		}

		int getVertsRealSize() {
			return sizeof(float) * (NUM_VERT_DATA * vertices.size());
		}

		int getIndsRealSize() {
			return sizeof(std::uint32_t) * indices.size();
		}
	};
}
