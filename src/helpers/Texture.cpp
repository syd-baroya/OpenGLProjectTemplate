#include"Texture.h"

Texture::Texture(const char* image, const char* texType, GLuint slot)
{
	path = image;
	// Assigns the type of the texture ot the texture object
	type = texType;

	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	//stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	if (!bytes) {
		std::cerr << "Failed to load image: " << image << std::endl;
		return;
	}
	std::cout << "Loaded image: " << image << ", Width: " << widthImg << ", Height: " << heightImg << ", Channels: " << numColCh << std::endl;

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) std::cerr << "OpenGL Error after glGenTextures: " << error << std::endl;

	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + slot);
	error = glGetError();
	if (error != GL_NO_ERROR) std::cerr << "OpenGL Error after glActiveTexture: " << error << std::endl;

	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);
	error = glGetError();
	if (error != GL_NO_ERROR) std::cerr << "OpenGL Error after glBindTexture (creation): " << error << std::endl;

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	error = glGetError();
	if (error != GL_NO_ERROR) std::cerr << "OpenGL Error after glTexParameteri (filter): " << error << std::endl;

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	error = glGetError();
	if (error != GL_NO_ERROR) std::cerr << "OpenGL Error after glTexParameteri (wrap): " << error << std::endl;

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Check what type of color channels the texture has and load it accordingly
	if (type == "normal") // prevents SRGB from deforming normals
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			widthImg,
			heightImg,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else if (type == "height")
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			widthImg,
			heightImg,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else if (numColCh == 4)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_SRGB_ALPHA,
			widthImg,
			heightImg,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else if (numColCh == 3)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_SRGB,
			widthImg,
			heightImg,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else if (numColCh == 1)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_SRGB,
			widthImg,
			heightImg,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			bytes
		);
	else
		throw std::invalid_argument("Automatic Texture type recognition failed");

	error = glGetError();
	if (error != GL_NO_ERROR) std::cerr << "OpenGL Error after glTexImage2D: " << error << std::endl;

	// Generates MipMaps
	glGenerateMipmap(GL_TEXTURE_2D);
	error = glGetError();
	if (error != GL_NO_ERROR) std::cerr << "OpenGL Error after glGenerateMipmap: " << error << std::endl;

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(GL_TEXTURE_2D, 0);
	error = glGetError();
	if (error != GL_NO_ERROR) std::cerr << "OpenGL Error after glBindTexture (unbinding): " << error << std::endl;
}

Texture::~Texture()
{
	destroy();
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) std::cerr << "OpenGL Error after glActiveTexture (bind): " << error << std::endl;

	glBindTexture(GL_TEXTURE_2D, ID);
	error = glGetError();
	if (error != GL_NO_ERROR) std::cerr << "OpenGL Error after glBindTexture (bind): " << error << std::endl;
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy()
{
	glDeleteTextures(1, &ID);
}