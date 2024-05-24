// void ANN::trainHelper(Mushroom* m) {
//     feedforward(m);

//     float targetValue = (m->getMushroomClass()) ? 1.0f : 0.0f;
//     float outputError = (targetValue - sigmoid(outputLayer[0]->getInput())) * sigmoidDerivative(outputLayer[0]->getInput());

//     std::vector<float> hiddenLayerErrors(numNeuronsPerHiddenLayer);

//     for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
//         hiddenLayerErrors[j] = outputError * outputWeights[j][0] * sigmoidDerivative(hiddenLayers[0][j]->getInput());
//     }

//     for (int i = 0; i < numNeuronsPerHiddenLayer; i++) {
//         outputWeights[i][0] += learningRate * outputError * sigmoid(hiddenLayers[0][i]->getInput());
//     }
//     outputBias += learningRate * outputError;

//     for (int i = 0; i < numInputs; i++) {
//         for (int j = 0; j < numNeuronsPerHiddenLayer; j++) {
//             weights[i][j] += learningRate * hiddenLayerErrors[j] * sigmoid(inputLayer[i]->getInput());
//         }
//     }
//     hiddenBias += learningRate * std::accumulate(hiddenLayerErrors.begin(), hiddenLayerErrors.end(), 0.0f);
// }

