#ifndef UPDATE_MATRIX_H
#define UPDATE_MATRIX_H

#include "../network.hpp"
#include "../types/vec_import.hpp"

Matrix DeepLearning::update_matrix(Matrix matrix, Normalize norm, ZAStorage za_storage, DeltaStorage delta_storage, float learning_rate) {
    printf("updating\n");
    int layers = matrix.b.size() - 1;
    printf("update firsts\n");
    matrix.w1 = matrix.w1 - dot(t(norm.x_norm), delta_storage.delta1) * learning_rate;
    matrix.b1 = matrix.b1 - sum(delta_storage.delta1) * learning_rate;
    printf("looping update\n");
    for (int i = 0; i < layers; i++) {
        matrix.w[i] = matrix.w[i] - dot(t(za_storage.a[i]), delta_storage.delta[i]) * learning_rate;
        matrix.b[i] = matrix.b[i] - sum(delta_storage.delta[i]) * learning_rate;
    }
    
    int last_a = za_storage.a.size() - 1;
    printf("updating lasts\n");
    matrix.w2 = matrix.w2 - dot(t(za_storage.a[last_a]), delta_storage.delta2) * learning_rate;
    matrix.b2 = matrix.b2 - sum(delta_storage.delta2) * learning_rate;

    printf("finished\n");
    return matrix;
}

#endif