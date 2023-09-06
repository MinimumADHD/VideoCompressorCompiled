#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

int main() {
    std::string videoPath;
    std::cout << "Enter the path to the video file: \n";
    std::getline(std::cin, videoPath);
    double targetFileSizeMB;
    std::cout << "Enter the target compressed file size in MB: \n";
    std::cin >> targetFileSizeMB;
    double originalVideoDurationSec;
    std::cout << "Enter the duration of the original video in seconds: \n";
    std::cin >> originalVideoDurationSec;
    std::string outputFormat;
    std::cout << "Enter the desired output format (e.g., mp4): \n";
    std::cin >> outputFormat;
    int targetBitrateKbps = static_cast<int>((targetFileSizeMB * 8192) / originalVideoDurationSec);
    std::stringstream ffmpegCommand;
    ffmpegCommand << "ffmpeg -i \"" << videoPath << "\" -c:v libx264 -b:v " << targetBitrateKbps
                  << "k -c:a aac -strict experimental -b:a 128k -movflags faststart ";
    std::string outputPath = "compressed_output." + outputFormat;
    ffmpegCommand << outputPath;
    int result = std::system(ffmpegCommand.str().c_str());
    if (result == 0) {
        std::cout << "Compression and conversion completed successfully. Output saved as " << outputPath << std::endl;
    } else {
        std::cerr << "An error occurred during compression and conversion." << std::endl;
    }
    return 0;
}