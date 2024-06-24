#include <iostream>
#include <raylib.h>
using namespace std;


//      Global Variables
//-------------------------------------------------------

// Enum for game events
typedef enum GameEvent {
    MENU,
    START,
    OPTIONS,
    CREDITS
} GameEvent;

// To scale things
float scale = 1.0f;

// Texture Variables Global declarations
Texture2D backIcon;
Texture2D optionsIcon;




//      Functions
//---------------------------------------------------------

// Functions to load and unload resources
void loadResources() {
    // Load back and options icon
    backIcon = LoadTexture("C:\\Users\\tobia\\OneDrive\\Documentos\\uptp 2024\\WordLab\\resources\\back_icon.png");
    optionsIcon = LoadTexture("C:\\Users\\tobia\\OneDrive\\Documentos\\uptp 2024\\WordLab\\resources\\options_icon.png");
    if (backIcon.id == 0 || optionsIcon.id == 0) {
        cout << "ERROR. Failed launching resources." << endl;
    }
}

void unloadResources() {
    // Unload the back icon and options icon texture
    UnloadTexture(optionsIcon);
    UnloadTexture(backIcon);
}

// Function to draw the return button and handle clicks
bool DrawReturnButton(Texture2D backIcon, float scale) {
    DrawTextureEx(backIcon, Vector2{ 8, 8 }, 0.0f, scale, WHITE);
    Rectangle backRect = { 10, 10, backIcon.width * scale, backIcon.height * scale };
    return CheckCollisionPointRec(GetMousePosition(), backRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

// Function to draw options button in every event
bool DrawOptionsButton(Texture2D optionsIcon, float scale) {
    DrawTextureEx(optionsIcon, Vector2{ 430, 12 }, 0.0f, scale, WHITE);
    Rectangle optRect = { 430, 12, optionsIcon.width * scale, optionsIcon.height * scale };
    return CheckCollisionPointRec(GetMousePosition(), optRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

// Function to draw a custom slider
float DrawSlider(float x, float y, float width, float height, float value) {
    Rectangle sliderBar = { x, y, width, height };
    Rectangle sliderKnob = { x + value * width - height / 2, y - height / 4, height / 2, height * 1.5f };

    // Draw the slider bar
    DrawRectangleRec(sliderBar, GRAY);

    // Check if the mouse is over the slider knob
    if (CheckCollisionPointRec(GetMousePosition(), sliderKnob) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        // Update the slider value based on mouse position
        value = (GetMouseX() - x) / width;
        if (value < 0.0f) value = 0.0f;
        if (value > 1.0f) value = 1.0f;
    }

    // Draw the slider knob
    DrawRectangleRec(sliderKnob, WHITE);

    return value;
}




//      Colorssss settings
//-----------------------------------------------------------------

// Define colors for text and button
Color titleColor = WHITE;
Color buttonBackgroundColor = BLUE;
Color buttonTextColor = WHITE;



//      Global Variables for Options
//-----------------------------------------------------------------

// Variables for options settings
bool showTutorial = true;
const char* languages[] = { "English", "Spanish" };
int currentLanguage = 0;
float musicVolume = 0.5f;
float sfxVolume = 0.5f;




/*

        Start Game GUI

*/

// Define constants
const int screenWidth = 500;
const int screenHeight = 700;
const int rows = 6;
const int cols = 5;
const int squareSize = 60;
const int frameThickness = 2;
const int squareSpacing = 15;

// Function to draw the grid of squares which are for input letters
void DrawGrid() {
    // Calculate the start position to center the grid
    float startX = 62;
    float startY = 128;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float posX = startX + col * (squareSize + squareSpacing);
            float posY = startY + row * (squareSize + squareSpacing);
            DrawRectangle(posX, posY, squareSize, squareSize, LIGHTGRAY);
            DrawRectangleLinesEx(Rectangle{ (float)posX, (float)posY, (float)squareSize, (float)squareSize }, frameThickness, WHITE);

            // If mouse hovering, change mouse to pointing appearence
            bool ishoveringSquare = CheckCollisionPointRec(GetMousePosition(), Rectangle{ startX, startY, posX - startX, posY - startY });
            (ishoveringSquare) ? SetMouseCursor(MOUSE_CURSOR_POINTING_HAND) : SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            // If click, allow input
            bool wasSquareClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (wasSquareClicked);

        }
    }
}



/*

        Running Game Instance

*/

int main() {

    // Raylib logging for debugging
    SetTraceLogLevel(LOG_DEBUG);

    // Initializing window
    InitWindow(screenWidth, screenHeight, "WordLab");

    // Loading textures
    loadResources();

    // Set target FPS for smooth animation
    SetTargetFPS(60);

    // Current game state
    GameEvent currentEvent = MENU;

    // Game loop
    while (!WindowShouldClose()) {
        // Update and draw based on current game state
        switch (currentEvent) {
        case MENU: {
            // Start drawing on frame
            BeginDrawing();

            // Clear the screen with black background
            ClearBackground(BLACK);

            // Font size for the title text
            int fontSize = 50;
            const char* titleText = "WORDLAB";

            // Calculate the width of the title text
            int titleTextWidth = MeasureText(titleText, fontSize);

            // Calculate the center position for the title text
            int titleX = (screenWidth / 2) - (titleTextWidth / 2);
            int titleY = screenHeight / 6;

            // Draw the title text
            DrawText(titleText, titleX, titleY, fontSize, titleColor);

            // Define button dimensions and position
            float buttonWidth = 200;
            float buttonHeight = 50;
            float buttonX = screenWidth / 2 - buttonWidth / 2;

            // Button labels and positions
            const char* buttonTexts[] = { "START", "OPTIONS", "CREDITS", "EXIT" };
            float buttonYPositions[] = { (screenHeight / 2) - 100, (screenHeight / 2) - 40, (screenHeight / 2) + 20, (screenHeight / 2) + 80 };

            // Draw buttons
            for (int i = 0; i < 4; i++) {
                float buttonY = buttonYPositions[i];

                // Check if mouse is hovering over the button
                bool isHoveringButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{ buttonX, buttonY, buttonWidth, buttonHeight });

                // Change button background color based on hover state
                if (isHoveringButton) {
                    buttonBackgroundColor = SKYBLUE;
                }
                else {
                    buttonBackgroundColor = BLUE;
                }

                // Draw the button rectangle
                DrawRectangle(buttonX, buttonY, buttonWidth, buttonHeight, buttonBackgroundColor);

                // Calculate the width of the button text
                int buttonTextWidth = MeasureText(buttonTexts[i], 20);

                // Calculate the center position for the button text
                int buttonTextX = (int)(buttonX + (buttonWidth / 2)) - (buttonTextWidth / 2);
                int buttonTextY = buttonY + (buttonHeight - 20) / 2;

                // Draw the button text
                DrawText(buttonTexts[i], buttonTextX, buttonTextY, 20, buttonTextColor);

                // Handle button clicks
                if (isHoveringButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (i == 0) currentEvent = START; // Start button
                    else if (i == 1) currentEvent = OPTIONS; // Options button
                    else if (i == 2) currentEvent = CREDITS; // Credits button
                    else if (i == 3) CloseWindow(); // Exit button
                }
            }

            // End drawing on frame
            EndDrawing();
        } break;

        case START: {
            // Start drawing on frame
            BeginDrawing();
            ClearBackground(DARKGRAY);

            // Draw the return button and checks for click
            if (DrawReturnButton(backIcon, scale)) {
                currentEvent = MENU;
            }

            // Draw options button and checks for click
            if (DrawOptionsButton(optionsIcon, scale)) {
                currentEvent = OPTIONS;
            }

            // If mouse hovering, change mouse to pointing appearence
            bool ishoveringBack = CheckCollisionPointRec(GetMousePosition(), Rectangle{  });
            (ishoveringBack) ? SetMouseCursor(MOUSE_CURSOR_POINTING_HAND) : SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            // Display gameplay screen content
            DrawText("WORDLAB", screenWidth / 2 - MeasureText("WORDLAB", 21), 22, 42, WHITE);

            /*
                    Start of game logic
            */

            // Drawing grid for input letters
            DrawGrid();

            // End drawing on frame
            EndDrawing();

        } break;

        case OPTIONS: {
            // Start drawing on frame
            BeginDrawing();
            ClearBackground(DARKBLUE);

            // Draw the return button and check for click
            if (DrawReturnButton(backIcon, scale)) {
                currentEvent = MENU;
            }

            // Display options screen content
            float optionsY = 150;
            DrawText("OPTIONS", screenWidth / 2 - MeasureText("OPTIONS", 40) / 2, 50, 40, WHITE);

            // Toggle tutorial
            DrawText(TextFormat("Show Tutorial: %s", showTutorial ? "ON" : "OFF"), 50, optionsY, 20, WHITE);
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 50, optionsY, 200, 20 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                showTutorial = !showTutorial;
            }
            optionsY += 40;

            // Language selection
            DrawText(TextFormat("Language: %s", languages[currentLanguage]), 50, optionsY, 20, WHITE);
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 50, optionsY, 200, 20 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                currentLanguage = (currentLanguage + 1) % 3;
            }
            optionsY += 40;

            // Music volume
            DrawText(TextFormat("Music Volume: %.2f", musicVolume), 50, optionsY, 20, WHITE);
            musicVolume = DrawSlider(250, optionsY, 200, 20, musicVolume);
            optionsY += 40;

            // SFX volume
            DrawText(TextFormat("SFX Volume: %.2f", sfxVolume), 50, optionsY, 20, WHITE);
            sfxVolume = DrawSlider(250, optionsY, 200, 20, sfxVolume);
            optionsY += 40;

            // Reset progress button
            DrawText("Reset Progress", 50, optionsY, 20, RED);
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ 50, optionsY, 200, 20 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Reset progress logic here
            }

            // End drawing on frame
            EndDrawing();
        } break;

        case CREDITS: {
            // Start drawing on frame
            BeginDrawing();

            // Draw the return button and check for click
            if (DrawReturnButton(backIcon, scale)) {
                currentEvent = MENU;
            }

            // Clear the screen with a different background color
            ClearBackground(DARKGREEN);

            // Display credits screen content
            DrawText("Credits", screenWidth / 2 - MeasureText("Credits", 60) / 2, 50, 60, WHITE);
            DrawText("Tobias Anuf", screenWidth / 2 - MeasureText("Tobias Anuf", 20) / 2, 220, 20, WHITE);
            DrawText("Angie Barreto", screenWidth / 2 - MeasureText("Angie Barreto", 20) / 2, 260, 20, WHITE);
            DrawText("Bryan ...", screenWidth / 2 - MeasureText("Bryan ...", 20) / 2, 300, 20, WHITE);
            DrawText("Lujan Martinez", screenWidth / 2 - MeasureText("Lujan Martinez", 20) / 2, 340, 20, WHITE);

            // End drawing on frame
            EndDrawing();

        } break;

        default: break;
        }
    }

    // Close the raylib window
    CloseWindow();
}