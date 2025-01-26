from fastapi import FastAPI
from fastapi.responses import FileResponse
from pydantic import BaseModel
import numpy as np
from typing import List
import matplotlib
import matplotlib.pyplot as plt
import kmeans_chebyshev
import json
#import seaborn as sns

matplotlib.use('Agg')  # Usar backend no interactivo
app = FastAPI()

# Definir el modelo para el vector
class VectorF(BaseModel):
    vector: List[float]
    

@app.post("/kmeans-chebyshev")
def calculo(seed: int, samples: int, n_clusters: int, n_features: int, max_iters: int):
    np.random.seed(seed)
    n_samples = samples
    #n_features = 2   # Número de características (dimensiones)

    # Crear tres grupos de datos distribuidos aleatoriamente
    data1 = np.random.normal(loc=[2, 2], scale=0.8, size=(n_samples // 3, n_features))
    data2 = np.random.normal(loc=[8, 8], scale=0.8, size=(n_samples // 3, n_features))
    data3 = np.random.normal(loc=[5, 0], scale=0.8, size=(n_samples // 3, n_features))

    # Unir los datos en un solo conjunto
    data = np.vstack((data1, data2, data3))

    # Convertir a lista para compatibilidad con el módulo C++
    data_list = data.tolist()

    # Crear y entrenar el modelo
    
    kmeans = kmeans_chebyshev.KMeansChebyshev(clusters=n_clusters, max_iterations=max_iters)
    kmeans.fit(data_list)

    # Obtener las etiquetas de predicción y los centroides
    labels = kmeans.predict(data_list)
    centroids = np.array(kmeans.get_centroids())

    # Graficar los datos y los clusters
    plt.figure(figsize=(10, 8))

    # Dibujar puntos de datos, coloreados por su cluster
    for i in range(len(data)):
        plt.scatter(data[i][0], data[i][1], c=f"C{labels[i]}", s=50, alpha=0.6)

    # Dibujar los centroides
    plt.scatter(centroids[:, 0], centroids[:, 1], c="black", marker="x", s=200, label="Centroids")

    # Estilo de la gráfica
    plt.title(f"K-Means Clustering (num muestras={n_samples}) con Chebyshev Distance", fontsize=16)
    plt.xlabel("Feature 1", fontsize=12)
    plt.ylabel("Feature 2", fontsize=12)
    plt.legend(loc="best")
    plt.grid(True)

    output_file = 'chebyshev.png'
    plt.savefig(output_file)
    plt.close()
    # Regresar el archivo como respuesta

    j1 = {
        "Grafica": output_file
    }
    jj = json.dumps(str(j1))

    return jj

@app.get("/kmeans-chebyshev-graph")
def getGraph(output_file: str):
    return FileResponse(output_file, media_type="image/png", filename=output_file)