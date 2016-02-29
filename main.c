#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

int handleMouse(int x, int y, SDL_Rect rect) {
    printf("%i %i\n", x, y);
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
        return 0;
    return 1;
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    int win_w = 320;
    int win_h = 240;

    SDL_Window *window = SDL_CreateWindow("Sdl2 Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, SDL_WINDOW_OPENGL);
    SDL_Surface *screen = SDL_GetWindowSurface(window);
    SDL_Surface *button_image = IMG_Load("button.jpg");

    int w = button_image->w;
    int h = button_image->h;

    int x = rand() % (win_w - w);
    int y = rand() % (win_h - h);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = win_w;
    rect.h = win_h;

    SDL_Event event;
    int running = 1;

    while (running) {
        // Event check
        SDL_MouseButtonEvent *mouse_event;
        while (SDL_PollEvent(&event) != 0) {
            switch(event.type) {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouse_event = &event;
                running = handleMouse(mouse_event->x, mouse_event->y, rect);
                break;
            }
        }
        // Redraw scene
        SDL_FillRect(screen, 0, 0xffffff);
        SDL_BlitSurface(button_image, 0, screen, &rect);
        // Update window
        SDL_UpdateWindowSurface(window);
    }

    SDL_FreeSurface(button_image);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
