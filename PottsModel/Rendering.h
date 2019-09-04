#pragma once

using namespace std;

void SaveLatticePicture(string filename, uint8_t numberOfStates);
void SaveLatticeRawPicture(string filename, uint8_t numberOfStates);
void SaveLatticeWithoutWhite(string filename, uint8_t numberOfStates);
void LoadLatticeFromFile(string filename, uint8_t numberOfStates);
