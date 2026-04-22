#include <fstream>
#include <cmath>

int main() {
    // Create PPM file for a colorful Hawaii vacation icon
    std::ofstream ppmFile("hawaii_icon.ppm");
    
    // Image dimensions
    int width = 200;
    int height = 200;
    int maxColorValue = 255;
    
    // Write PPM header
    ppmFile << "P3\n";
    ppmFile << width << " " << height << "\n";
    ppmFile << maxColorValue << "\n";
    
    // Generate pixel data with nested loops
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int red, green, blue;
            
            // Calculate distance from center for gradient effects
            float centerX = width / 2.0;
            float centerY = height / 2.0;
            float distFromCenter = std::sqrt((x - centerX) * (x - centerX) + 
                                            (y - centerY) * (y - centerY));
            
            // Create gradient sky/ocean background
            if (y < 100) {
                // Sky gradient (blue to orange for sunset)
                float skyGradient = (float)y / 100.0;
                red = (int)(255 * skyGradient + 0 * (1 - skyGradient));
                green = (int)(200 * skyGradient + 100 * (1 - skyGradient));
                blue = (int)(100 * skyGradient + 200 * (1 - skyGradient));
            } else {
                // Ocean gradient (blue-green)
                red = 0;
                green = (int)(150 + 50 * std::sin((x + y) * 0.02));
                blue = (int)(200 - 30 * std::sin((x - y) * 0.02));
            }
            
            // Draw a yellow sun
            float sunRadius = 30;
            float sunDistFromCenter = std::sqrt((x - centerX) * (x - centerX) + 
                                               (y - 70) * (y - 70));
            if (sunDistFromCenter < sunRadius) {
                red = 255;
                green = 220;
                blue = 0;
            }
            
            // Draw palm tree trunk (brown vertical line)
            if (x > 85 && x < 115 && y > 120 && y < 180) {
                red = 139;
                green = 69;
                blue = 19;
            }
            
            // Draw palm tree fronds (bright green leaves)
            int palmCenterX = 100;
            int palmCenterY = 110;
            
            // Multiple fronds radiating from palm top
            for (int leaf = 0; leaf < 8; leaf++) {
                float angle = (leaf * 3.14159 * 2) / 8.0;
                int leafX = palmCenterX + (int)(50 * std::cos(angle));
                int leafY = palmCenterY + (int)(50 * std::sin(angle));
                
                // Draw thick leaf lines
                int distToLeaf = std::sqrt((x - leafX) * (x - leafX) + 
                                          (y - leafY) * (y - leafY));
                if (distToLeaf < 3) {
                    red = 34;
                    green = 200;
                    blue = 50;
                }
            }
            
            // Add some bright pink/magenta flowers randomly scattered
            if ((x % 40 == 10 && y % 40 == 10) || 
                (x % 45 == 15 && y % 45 == 20)) {
                red = 255;
                green = 20;
                blue = 147;
            }
            
            // Ensure color values are in valid range
            red = (red < 0) ? 0 : (red > 255) ? 255 : red;
            green = (green < 0) ? 0 : (green > 255) ? 255 : green;
            blue = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;
            
            // Write RGB values
            ppmFile << red << " " << green << " " << blue << "\n";
        }
    }
    
    ppmFile.close();
    return 0;
}