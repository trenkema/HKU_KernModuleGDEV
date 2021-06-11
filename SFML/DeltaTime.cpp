#include "DeltaTime.h"

DeltaTime::DeltaTime() {};

DeltaTime::~DeltaTime() {};

void DeltaTime::UpdateDT() {
    this->dt = this->clock.restart().asSeconds();
}

float DeltaTime::GetDT() const {
    return this->dt;
}
