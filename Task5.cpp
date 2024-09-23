#include <QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <opencv2/opencv.hpp>

class ImageProcessingTool : public QMainWindow {
    Q_OBJECT

public:
    ImageProcessingTool(QWidget *parent = nullptr) : QMainWindow(parent) {
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        QPushButton *loadButton = new QPushButton("Load Image", this);
        QPushButton *saveButton = new QPushButton("Save Image", this);
        QPushButton *grayscaleButton = new QPushButton("Grayscale", this);
        QPushButton *blurButton = new QPushButton("Blur", this);
        QPushButton *resizeButton = new QPushButton("Resize", this);
        QPushButton *cropButton = new QPushButton("Crop", this);

        layout->addWidget(loadButton);
        layout->addWidget(saveButton);
        layout->addWidget(grayscaleButton);
        layout->addWidget(blurButton);
        layout->addWidget(resizeButton);
        layout->addWidget(cropButton);

        imageLabel = new QLabel(this);
        layout->addWidget(imageLabel);

        connect(loadButton, &QPushButton::clicked, this, &ImageProcessingTool::loadImage);
        connect(saveButton, &QPushButton::clicked, this, &ImageProcessingTool::saveImage);
        connect(grayscaleButton, &QPushButton::clicked, this, &ImageProcessingTool::applyGrayscale);
        connect(blurButton, &QPushButton::clicked, this, &ImageProcessingTool::applyBlur);
        connect(resizeButton, &QPushButton::clicked, this, &ImageProcessingTool::resizeImage);
        connect(cropButton, &QPushButton::clicked, this, &ImageProcessingTool::cropImage);
    }

private slots:
    void loadImage() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.xpm *.jpg)");
        if (!fileName.isEmpty()) {
            image = cv::imread(fileName.toStdString());
            displayImage();
        }
    }

    void saveImage() {
        QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "Images (*.png *.xpm *.jpg)");
        if (!fileName.isEmpty()) {
            cv::imwrite(fileName.toStdString(), image);
        }
    }

    void applyGrayscale() {
        if (!image.empty()) {
            cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
            displayImage();
        }
    }

    void applyBlur() {
        if (!image.empty()) {
            cv::GaussianBlur(image, image, cv::Size(15, 15), 0);
            displayImage();
        }
    }

    void resizeImage() {
        if (!image.empty()) {
            int newWidth = 200; // Set your desired width
            int newHeight = 200; // Set your desired height
            cv::resize(image, image, cv::Size(newWidth, newHeight));
            displayImage();
        }
    }

    void cropImage() {
        if (!image.empty()) {
            cv::Rect roi(50, 50, 200, 200); // Change the parameters for cropping
            image = image(roi);
            displayImage();
        }
    }

    void displayImage() {
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB); // Convert to RGB format
        QImage qimg(image.data, image.cols, image.rows, image.step[0], QImage::Format_RGB888);
        imageLabel->setPixmap(QPixmap::fromImage(qimg));
    }

private:
    cv::Mat image;
    QLabel *imageLabel;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ImageProcessingTool window;
    window.resize(800, 600);
    window.setWindowTitle("Image Processing Tool");
    window.show();
    return app.exec();
}

