#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

namespace py = pybind11;

class KMeansChebyshev {
private:
    int k;  // Número de clusters
    int max_iters;  // Iteraciones máximas
    std::vector<std::vector<double>> centroids;

    // Método para calcular la distancia de Chebyshev
    double chebyshev_distance(const std::vector<double>& point1, const std::vector<double>& point2) {
        double max_diff = 0.0;
        for (size_t i = 0; i < point1.size(); ++i) {
            max_diff = std::max(max_diff, std::abs(point1[i] - point2[i]));
        }
        return max_diff;
    }

    // Asignar cada punto al cluster más cercano
    std::vector<int> assign_clusters(const std::vector<std::vector<double>>& data) {
        std::vector<int> labels(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            double min_dist = std::numeric_limits<double>::max();
            int best_cluster = -1;
            for (int j = 0; j < k; ++j) {
                double dist = chebyshev_distance(data[i], centroids[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_cluster = j;
                }
            }
            labels[i] = best_cluster;
        }
        return labels;
    }

    // Recalcular los centroides
    void update_centroids(const std::vector<std::vector<double>>& data, const std::vector<int>& labels) {
        std::vector<std::vector<double>> new_centroids(k, std::vector<double>(data[0].size(), 0.0));
        std::vector<int> counts(k, 0);

        for (size_t i = 0; i < data.size(); ++i) {
            int cluster = labels[i];
            for (size_t j = 0; j < data[i].size(); ++j) {
                new_centroids[cluster][j] += data[i][j];
            }
            counts[cluster]++;
        }

        for (int j = 0; j < k; ++j) {
            if (counts[j] > 0) {
                for (size_t l = 0; l < new_centroids[j].size(); ++l) {
                    new_centroids[j][l] /= counts[j];
                }
            }
        }

        centroids = std::move(new_centroids);
    }

public:
    KMeansChebyshev(int clusters, int max_iterations)
        : k(clusters), max_iters(max_iterations) {}

    void fit(const std::vector<std::vector<double>>& data) {
        // Inicialización de los centroides (usar los primeros k puntos como iniciales)
        centroids = std::vector<std::vector<double>>(data.begin(), data.begin() + k);

        for (int iter = 0; iter < max_iters; ++iter) {
            // Asignar clusters
            std::vector<int> labels = assign_clusters(data);

            // Recalcular los centroides
            update_centroids(data, labels);
        }
    }

    std::vector<int> predict(const std::vector<std::vector<double>>& data) {
        return assign_clusters(data);
    }

    std::vector<std::vector<double>> get_centroids() const {
        return centroids;
    }
};

// Enlace Pybind11
PYBIND11_MODULE(kmeans_chebyshev, m) {
    py::class_<KMeansChebyshev>(m, "KMeansChebyshev")
        .def(py::init<int, int>(), py::arg("clusters"), py::arg("max_iterations"))
        .def("fit", &KMeansChebyshev::fit, py::arg("data"))
        .def("predict", &KMeansChebyshev::predict, py::arg("data"))
        .def("get_centroids", &KMeansChebyshev::get_centroids);
}
