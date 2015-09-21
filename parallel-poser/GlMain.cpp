#include "GlMain.h"
#include "GL/glut.h"

GlMain::GlMain(void)
{
}
GlMain::~GlMain(void)
{
}

void GlMain::UpdateDisplay()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	/* preserve modelview matrix */
	//glPushMatrix();

	/* rotate by angle degrees around the axis y = x */
	glRotatef(1.0f, 1.0f, 1.0f, 0.0f);
	//glScalef(50.0f, 50.0f, 50.0f);

	/* render a solid teapot */
	//glutWireTeapot(1.0f);
	Render();

	/* return to previous modelview matrix */
	//glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

GlMain::GlMain(int argc, char **argv, std::string filename, const aiScene* scene)
{
	//models.push_back(Model(filename));
	GlMain::scene = scene;
	printf("File imported.\n");

	// initialise OpenGL
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutCreateWindow("PARAC-LOAPSO Render");

	//Set up our camera
	glViewport(0, 0, (GLsizei)640, (GLsizei)480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-(float)640 / 2, (float)640 / 2, -(float)480 / 2, (float)480 / 2, -10000, 10000);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 3, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // clear the matrix
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//turn on some hidden surface removal
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); //remove back facing triangles
	glEnable(GL_DEPTH_TEST); //turn on z buffer

							 //enable multisampling
	glEnable(GLUT_MULTISAMPLE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON);
	glShadeModel(GL_FLAT);
}

void GlMain::Render()
{
	unsigned int i;
	unsigned int n = 0, t;
	//struct aiMatrix4x4 mat = nd->mTransformation;
	// update transform

	//aiTransposeMatrix4(&mat);
	glPushMatrix();
	//glMultMatrixf((float*)&mat);

	// draw all meshes assigned to this node
	for (n = 0; n < scene->mNumMeshes; n++) {
		const struct aiMesh* mesh = scene->mMeshes[n];
		for (t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;
			switch (face->mNumIndices) {
			case 1: face_mode = GL_POINTS; break;
			case 2: face_mode = GL_LINES; break;
			case 3: face_mode = GL_TRIANGLES; break;
			default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);
			for (i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				if (mesh->mColors[0] != NULL)
					glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				if (mesh->mNormals != NULL)
					glNormal3fv(&mesh->mNormals[index].x);
				glVertex3fv(&mesh->mVertices[index].x);
			}
			glEnd();
		}
	}
	glPopMatrix();
}