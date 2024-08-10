#include "graphics/renderer.hpp"

RenderWindow::RenderWindow() {
    render_width_ = 20;
    max_window_length_ = 100;
    render_offset_ = 0;
}

RenderWindow::RenderWindow(unsigned int render_width, unsigned int max_window_length) : render_width_(render_width), max_window_length_(max_window_length), render_offset_(0) {}

int RenderWindow::get_render_offset() const {
    return render_offset_;
}

void RenderWindow::update_offset_left() {
    if (render_offset_ <= 0) { // Render window is already as far left as it can go so nothing needs to be done
        return;
    }
    --render_offset_; // Move the offset back one (this value could be played around with in the future)
}

void RenderWindow::update_offset_right() {
    if (render_offset_ + render_width_ >= max_window_length_) { // Render window is already as far right as it can go so nothing needs to be done
        return;
    }
    ++render_offset_; //Move the offset forward one (this value could be played around with in the future)
}


void RenderWindow::normalize_vb(const float* un_normalized_buff, float* normalized_buff, unsigned int count) {
    for (int i = 0; i < count; ++i) { 
        if (i % 2 == 0) { // Since arrays are 2d vectors and we only want to look at x values only normalize on even indicies
            normalized_buff[i] = ((un_normalized_buff[i] - render_offset_) / (render_width_ / 2.0)) - 1;
        } else {
            normalized_buff[i] = un_normalized_buff[i];
        }
    }
}


void RenderWindow::draw_object(unsigned int &vao, VertexBuffer &vbo, IndexBuffer &ibo) {
    vbo.Bind();
    ibo.Bind();
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
