#include "raylib.h"
#include <stdio.h>

#define GRID_SIZE  10    // Kare sayısı (10x10)
#define CELL_SIZE  70    // Her bir karenin boyutu
#define HEALTH_BAR_WIDTH 10    // Can barının genişliği
#define HEALTH_BAR_HEIGHT 50   // Can barının yüksekliği
#define MAX_UNITS_PER_CELL 100   // Her hücrede maksimum birim sayısı

typedef struct {
    int count;          // Birim sayısı
    float health;      // Birim sağlığı (0.0 - 1.0 arasında)
    Texture2D texture; // Birim resmi
} Unit;

int main(void)
{
    // Pencereyi başlat
    InitWindow(GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE, "10x10 Grid Üzerinde Görseller");

    // Görselleri yükle
    Texture2D textures[10];
    const char *imagePaths[10] = {
        "C:\\Users\\sezer\\OneDrive\\Resimler\\yeni_piyade.png",
        "C:\\Users\\sezer\\OneDrive\\Resimler\\yeni_okcu.png",
        "C:\\Users\\sezer\\OneDrive\\Resimler\\yeni_suvari.png",
        "C:\\Users\\sezer\\OneDrive\\Resimler\\yeni_kusatma.png",
        "C:\\Users\\sezer\\OneDrive\\Resimler\\yeni_ork.png",
        "C:\\Users\\sezer\\OneDrive\\Resimler\\yeni_mizrak.png",
        "C:\\Users\\sezer\\OneDrive\\Resimler\\yeni_varg.png",
        "C:\\Users\\sezer\\OneDrive\\Resimler\\yeni_troll.png",
        "C:\\Users\\sezer\\OneDrive\\Resimler\\yeni_canavar.png",
        "C:\\Users\\sezer\\OneDrive\\Resimler\\yeni_kahraman.png"
    };

    // Görselleri yükle
    for (int i = 0; i < 10; i++) {
        textures[i] = LoadTexture(imagePaths[i]);
        // Görselin başarılı bir şekilde yüklenip yüklenmediğini kontrol et
        if (textures[i].id == 0) {
            printf("Görsel yüklenemedi: %s\n", imagePaths[i]);
            CloseWindow(); // Pencereyi kapat
            return 1; // Hata durumu
        }
    }

    // Birimleri tanımla
    Unit cavalry = {500, 1.0f, textures[2]}; // 500 süvari
    Unit infantry = {100, 1.0f, textures[0]}; // 100 piyade
    Unit archers = {100, 1.0f, textures[1]};  // 100 okçu

    // Dikey sağlık barları için tanımlama
    int cellUnits[GRID_SIZE][GRID_SIZE] = {0}; // Her hücredeki birim sayısını tutar
    float cellHealth[GRID_SIZE][GRID_SIZE] = {0.0f}; // Her hücredeki sağlık durumunu tutar

    // Birimleri hücrelere dağıt
    for (int i = 0; i < cavalry.count; i++) {
        int row = (i / MAX_UNITS_PER_CELL) / GRID_SIZE; // Satır
        int col = (i / MAX_UNITS_PER_CELL) % GRID_SIZE; // Sütun
        cellUnits[row][col] += 1; // Hücredeki birim sayısını artır
        cellHealth[row][col] = cavalry.health; // Hücredeki sağlık durumunu ayarla
    }

    SetTargetFPS(60);  // FPS ayarla

    while (!WindowShouldClose())  // Pencere kapatılmadığı sürece
    {
        BeginDrawing();
        ClearBackground(RAYWHITE); // Arka planı temizle

        // 10x10 grid çizimi
        for (int row = 0; row < GRID_SIZE; row++)
        {
            for (int col = 0; col < GRID_SIZE; col++)
            {
                int x = col * CELL_SIZE;
                int y = row * CELL_SIZE;

                DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, LIGHTGRAY); // Grid hücrelerini çiz
                DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, DARKGRAY); // Çizgi ekle

                // Hücredeki birimleri göster
                if (cellUnits[row][col] > 0) {
                    DrawTextureEx(cavalry.texture, (Vector2){x + 5, y + 5}, 0.0f, 1.0f, WHITE);
                    DrawText(TextFormat("%d", cellUnits[row][col]), x + 5, y + 5, 20, BLACK);
                    
                    // Dikey sağlık barı
                    int filledHeight = HEALTH_BAR_HEIGHT * cellHealth[row][col];
                    DrawRectangle(x + CELL_SIZE + 10, y + (HEALTH_BAR_HEIGHT - filledHeight) + 10, 
                                  HEALTH_BAR_WIDTH, filledHeight, GREEN); // Dolu kısım
                    DrawRectangle(x + CELL_SIZE + 10, y + 10, 
                                  HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT - filledHeight, RED); // Boş kısım
                }
            }
        }

        EndDrawing();
    }

    // Kaynakları serbest bırak
    for (int i = 0; i < 10; i++) {
        UnloadTexture(textures[i]); // Yüklenen görselleri serbest bırak
    }
    CloseWindow(); // Pencereyi kapat

    return 0;
}
