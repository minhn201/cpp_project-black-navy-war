#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
#include "graphics/index_buffer.hpp"
#include "graphics/vertex_buffer.hpp"

class RenderWindow {
    private:
        unsigned int render_width_; // How wide the rendered area is
        unsigned int max_window_length_; // How long/wide the entire window will be
        int render_offset_; // The current offset of where to render (can be updated by pressing the arrow keys)

    public:
        RenderWindow();
        RenderWindow(unsigned int render_width, unsigned int max_window_length);

        int get_render_offset() const; // Returns the current render offset
        void update_offset_left(); // Decreases the render offset
        void update_offset_right(); // Increases the render offset

        // Precondition: values inside the vertex buffer are within 0 and max_window_length_
        // Takes in a vertex buffer with verticies in the range 0 to max_window_length_
        // Normalizes the vertices upon the x axis so the x values are within -1 and 1.
        void normalize_vb(const float* un_normalized_buff, float* normalized_buff, unsigned int count);

        // Draws the given object to the screen based on the provided buffers.
        // Assumes that the values have already been normalized within the given RenderWindow context
        // If values are not normalized to be within the range [-1,1] they will not be shown
        // This function assumes objects to be drawn are GL_TRIANGLES
        void draw_object(unsigned int &vao, VertexBuffer &vbo, IndexBuffer &ibo);
};

#endif