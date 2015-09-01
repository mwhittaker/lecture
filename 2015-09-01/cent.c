#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned int uint;

// (x, y) coordinate
typedef struct {
    double x;
    double y;
} coordinate;

// Returns a random (x, y) coordinate where x and y are uniformally drawn from
// the range [0, max].
coordinate random_coordinate(const double max) {
    const double x = ((double) rand()) / ((double) RAND_MAX);
    const double y = ((double) rand()) / ((double) RAND_MAX);
    return (coordinate){x * max, y * max};
}

// Returns n random coordinates.
coordinate *random_coordinates(const uint n) {
    coordinate *coordinates = (coordinate *)calloc(n, sizeof(coordinate));
    assert (coordinates != NULL);
    for (uint i = 0; i < n; ++i) {
        coordinates[i] = random_coordinate(100.);
    }
    return coordinates;
}

// Unzips a list of coordinates into a list of xs and a list of ys.
void unzip(const coordinate *coordinates, const uint n, double **xs, double **ys) {
    *xs = (double *)calloc(n, sizeof(double));
    assert (xs != NULL);
    *ys = (double *)calloc(n, sizeof(double));
    assert (ys != NULL);

    for (uint i = 0; i < n; ++i) {
        (*xs)[i] = coordinates[i].x;
        (*ys)[i] = coordinates[i].y;
    }
}

// a.  store an array of (x,y) coordinates; loop i and simultaneously
//     sum the xi and yi
coordinate centroid_a(const coordinate *coordinates, uint n) {
    coordinate centroid = {0.0, 0.0};
    for (uint i = 0; i < n; ++i) {
        const coordinate *c = &coordinates[i];
        centroid.x += c->x;
        centroid.y += c->y;
    }
    centroid.x /= n;
    centroid.y /= n;
    return centroid;
}

// b.  store an array of (x,y) coordinates; loop i and sum the xi,
//     then sum the yi in a separate loop
coordinate centroid_b(const coordinate *coordinates, uint n) {
    coordinate centroid = {0.0, 0.0};
    for (uint i = 0; i < n; ++i) {
        centroid.x += coordinates[i].x;
    }
    for (uint i = 0; i < n; ++i) {
        centroid.y += coordinates[i].y;
    }
    centroid.x /= n;
    centroid.y /= n;
    return centroid;
}


// c.  store the xi in one array, the yi in a second array.
//     sum the xi, then sum the yi.
coordinate centroid_c(const double *xs, const double *ys, uint n) {
    coordinate centroid = {0.0, 0.0};
    for (uint i = 0; i < n; ++i) {
        centroid.x += xs[i];
    }
    for (uint i = 0; i < n; ++i) {
        centroid.y += ys[i];
    }
    centroid.x /= n;
    centroid.y /= n;
    return centroid;
}

int main() {
    // coordinates
    const uint n = 1000 * 1000 * 50;
    coordinate *coordinates = random_coordinates(n);
    double *xs;
    double *ys;
    unzip(coordinates, n, &xs, &ys);

    // timing
    clock_t start;
    clock_t stop;
    clock_t diff;
    int msec;

    // a
    start = clock();
    coordinate ca = centroid_a(coordinates, n);
    stop = clock();
    diff = stop - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("%d\n", msec);

    // b
    start = clock();
    coordinate cb = centroid_b(coordinates, n);
    stop = clock();
    diff = stop - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("%d\n", msec);

    // c
    start = clock();
    coordinate cc = centroid_c(xs, ys, n);
    stop = clock();
    diff = stop - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("%d\n", msec);

    // print centroids
    printf("(%f, %f)\n", ca.x, ca.y);
    printf("(%f, %f)\n", cb.x, cb.y);
    printf("(%f, %f)\n", cc.x, cc.y);

    free(coordinates);
    free(xs);
    free(ys);
    return 0;
}
