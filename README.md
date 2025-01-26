El programa implementa el algoritmo de K-Means utilizando la distancia de Chebyshev como métrica para calcular las distancias entre puntos y centroides. Posteriormente, agrupa los datos en clusters y muestra los resultados en una gráfica. La distancia de Chebyshev mide la mayor diferencia absoluta entre las coordenadas correspondientes de dos puntos. Esto contrasta con otras métricas de distancia, como la distancia de Manhattan, que mide la suma de las diferencias absolutas entre las coordenadas de dos puntos.
Diferencias entre Distancia de Chebyshev y Manhattan
Característica	Chebyshev	Manhattan
Fórmula	( d(x, y) = \max_{i}(	x_i - y_i
Geometría	Representa el movimiento en un tablero de ajedrez (máximo desplazamiento en cualquier eje).	Representa distancias en una cuadrícula (como caminos en una ciudad).
Rango de Influencia	Determinado por la mayor diferencia en un solo eje.	Influenciado por la suma de todas las diferencias a lo largo de los ejes.
Sensibilidad	Más sensible a una característica dominante.	Proporciona un balance al considerar todos los ejes por igual.
Aplicaciones Comunes	Juegos de tablero, mapas discretos.	Análisis de datos, geometría urbana, series temporales.
¿Cuál es mejor para calcular distancias?

    Distancia de Chebyshev:
        Es ideal para problemas donde la distancia está limitada por un único eje dominante.
        Ejemplo: Movimientos en un tablero de ajedrez o en aplicaciones donde una sola característica puede ser crítica.
        Ventaja: Menos cálculo y más rápida en datasets grandes con una característica dominante.

    Distancia de Manhattan:
        Es mejor cuando quieres capturar la suma total de diferencias a lo largo de todas las dimensiones, proporcionando una medida más equilibrada.
        Ejemplo: Análisis de datos multidimensionales donde todas las características son igualmente importantes.
        Ventaja: Es más robusta en datasets con múltiples características relevantes.

Conclusión

    Usa Chebyshev cuando el problema depende de una característica dominante o quieres simplificar cálculos.
    Usa Manhattan cuando todas las características tienen importancia similar y necesitas un enfoque más equilibrado.
    En general, la elección depende de la naturaleza de los datos y del contexto del problema.
