# 🧠 ObjectSegmenter – Modular Object Segmentation with OpenCV (C++)

**ObjectSegmenter** is a modular, reusable C++ library built on top of OpenCV for industrial-grade object segmentation and geometric analysis.

It is designed to be plugged into real-time computer vision pipelines (e.g., inspection, counting, pick-and-place, defect detection) and supports:
- Preprocessing (grayscale, blur, thresholding, morphology)
- Contour-based object detection
- Centroid, area, perimeter, and bounding box extraction
- Annotated output for visual inspection
- Easy integration into threaded pipelines or embedded systems

---

## 🚀 Features

- 🔲 **Robust Binary Segmentation**: Otsu thresholding with Gaussian blur and optional inversion
- 📦 **Contour-Based Object Detection**: Uses `cv::findContours()` in `RETR_EXTERNAL` mode
- 🧮 **Geometric Measurements**: Area, perimeter, bounding box, centroid
- 🖼️ **Visual Output**: Contours, bounding boxes, centroids, object ID overlays
- 🧩 **Modular Design**: Clean C++ class with no global state — plug-and-play friendly

---

## 📁 File Structure

/project-root │
  ├── ObjectData.h # Struct to hold per-object data
  ├── ObjectSegmenter.h # Header for segmentation module
  ├── ObjectSegmenter.cpp # Implementation of segmentation logic
  ├── main.cpp # Example usage entry point 
  └── README.md # This file


---

## 🛠️ Dependencies

- **OpenCV 4.x**
- **C++17** standard compiler (tested with `g++ 11+`)
- Linux/macOS/Windows compatible

Install OpenCV with:
```bash
sudo apt install libopencv-dev
```

## 🔧 Build & Run

```bash
g++ main.cpp ObjectSegmenter.cpp -o object_segmenter `pkg-config --cflags --libs opencv4` -std=c++17
./object_segmenter
```

Ensure your image file (e.g., objects.jpg) is in the project directory.


## 🧪 Example Use Case

```cpp
ObjectSegmenter segmenter;
std::vector<ObjectData> results;
cv::Mat output;

segmenter.process(inputImage, output, results);

for (const auto& obj : results) {
    std::cout << "Object " << obj.id << ": Area = " << obj.area << ", Centroid = " << obj.centroid << std::endl;
}
```

## 🔄 Future Extensions (WIP Ideas)

- ObjectFilter module (by area, shape, orientation)
- Data export to CSV/JSON/SQL
- Integration with cv::dnn for defect classification
- Camera calibration and metric measurement (mm)

## 📄 License

MIT License — use it freely in commercial or academic projects.





