/*
    Project Corrode Graphics Engine (PCGE)
    mesh.hpp - holds and renders mesh data 
*/
#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glad.h>

#include <common/transform.hpp>
#include <shader.hpp>
#include <drawable.hpp>
#include <camera.hpp>

namespace Drawable{
    struct Vertex {
		glm::vec3 pos;
        glm::vec3 normal;
		glm::vec2 texCoord;
		glm::vec3 tangents;
    };

    struct Texture {
        unsigned int id;
        std::string type, path;
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
		std::vector<uint16_t> indices;
        // Textures 
        std::vector<Texture> textures;

		// Shader program
		std::shared_ptr<Rendering::ShaderProgram> shader; // Save this in case we find a use for keeping it here
		unsigned int shaderProgram;
	public:
		// Has our mesh been modified?
		bool modified = false;
        // Base transform
		Transform transform;
        /*
         *  VAO -> Tells OpenGL how our vertices are laid out
         *  VBO -> for our vertices
         *  EBO -> for our indices
         */
        unsigned int VBO, VAO, EBO;

		Mesh(std::vector<Vertex> verts, std::vector<uint16_t> inds, std::vector<Texture> textures, std::shared_ptr<Rendering::ShaderProgram> shader);

        void initMesh();

        void draw(const Rendering::Camera& cam) override;

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

		std::vector<uint16_t> getIndicies() {
			return indices;
		}

		void setIndicies(std::vector<uint16_t> inds) {
			this->indices = inds;
			modified = true;
		}

		int getVertsRealSize() {
			return sizeof(float) * (11 * vertices.size());
		}

		int getIndsRealSize() {
			return sizeof(float) * indices.size();
		}
	};
}