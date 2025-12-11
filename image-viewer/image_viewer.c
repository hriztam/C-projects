#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int main()
{
    // --- Init SDL ---
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    // --- Init SDL_image ---
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)))
    {
        printf("IMG_Init error: %s\n", IMG_GetError());
        return 1;
    }

    const int win_w = 800;
    const int win_h = 500;

    SDL_Window *pwindow = SDL_CreateWindow(
        "Image Viewer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        win_w, win_h,
        SDL_WINDOW_RESIZABLE);

    if (!pwindow)
    {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        return 1;
    }

    // --- Create renderer ---
    SDL_Renderer *prenderer =
        SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED);

    if (!prenderer)
    {
        printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
        return 1;
    }

    // --- Load image ---
    SDL_Surface *pimage = IMG_Load("michael.png");

    if (!pimage)
    {
        printf("IMG_Load error: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture *ptexture = SDL_CreateTextureFromSurface(prenderer, pimage);
    SDL_FreeSurface(pimage);

    int img_w, img_h;
    SDL_QueryTexture(ptexture, NULL, NULL, &img_w, &img_h);

    // destination rect (updated each render)
    SDL_Rect dst;

    // --- Main loop ---
    SDL_Event e;
    int running = 1;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = 0;

            // Handle resize
            if (e.type == SDL_WINDOWEVENT &&
                e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                // window size will be updated automatically
            }
        }

        // Get current window size (in case resized)
        int cur_w, cur_h;
        SDL_GetWindowSize(pwindow, &cur_w, &cur_h);

        // --- Compute scale to fit image ---
        float scale_w = (float)cur_w / img_w;
        float scale_h = (float)cur_h / img_h;
        float scale = (scale_w < scale_h) ? scale_w : scale_h;

        dst.w = img_w * scale;
        dst.h = img_h * scale;

        // Center the image
        dst.x = (cur_w - dst.w) / 2;
        dst.y = (cur_h - dst.h) / 2;

        // Render
        SDL_SetRenderDrawColor(prenderer, 0, 0, 0, 255);
        SDL_RenderClear(prenderer);

        SDL_RenderCopy(prenderer, ptexture, NULL, &dst);

        SDL_RenderPresent(prenderer);

        SDL_Delay(16);
    }

    SDL_DestroyTexture(ptexture);
    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
