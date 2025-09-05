#include "Tardigrade.h"
#include <algorithm>
#include <cmath>

Tardigrade::Tardigrade()
    : temperatura(20.0), radiacion(0.0), presion(1.0), hidratacion(80.0), currentState(TardigradeState::ACTIVE)
{
}

void Tardigrade::setTemperatura(double temp) {
    temperatura = temp;
}

void Tardigrade::setRadiacion(double rad) {
    radiacion = rad;
}

void Tardigrade::setPresion(double pres) {
    presion = pres;
}

void Tardigrade::setHidratacion(double hid) {
    hidratacion = hid;
}

double Tardigrade::getTemperatura() const {
    return temperatura;
}

double Tardigrade::getRadiacion() const {
    return radiacion;
}

double Tardigrade::getPresion() const {
    return presion;
}

double Tardigrade::getHidratacion() const {
    return hidratacion;
}

double Tardigrade::calcularFactorTemperatura() const {
    // Optimal range: -20°C to 40°C
    if (temperatura >= -20.0 && temperatura <= 40.0) {
        return 1.0;  // 100% survival
    } else if (temperatura >= -273.0 && temperatura <= 150.0) {
        // Can survive extreme temperatures in cryptobiosis
        double distance = std::min(std::abs(temperatura + 20.0), std::abs(temperatura - 40.0));
        return std::max(0.1, 1.0 - distance / 200.0);  // Gradual decline
    } else {
        return 0.0;  // Beyond survivable limits
    }
}

double Tardigrade::calcularFactorRadiacion() const {
    // Can survive up to 5,000 Gy
    if (radiacion <= 100.0) {
        return 1.0;  // No significant impact
    } else if (radiacion <= 5000.0) {
        return 1.0 - (radiacion - 100.0) / 4900.0;  // Gradual decline
    } else {
        return 0.0;  // Lethal dose
    }
}

double Tardigrade::calcularFactorPresion() const {
    // Can survive vacuum (0 atm) to extreme pressures (up to 600 atm)
    if (presion >= 0.5 && presion <= 2.0) {
        return 1.0;  // Optimal atmospheric pressure
    } else if (presion >= 0.0 && presion <= 600.0) {
        if (presion < 0.5) {
            return 0.3 + 0.7 * (presion / 0.5);  // Vacuum survival
        } else {
            return 1.0 - (presion - 2.0) / 598.0 * 0.7;  // High pressure decline
        }
    } else {
        return 0.0;  // Beyond survivable limits
    }
}

double Tardigrade::calcularFactorHidratacion() const {
    // Can survive dehydration (anhydrobiosis)
    if (hidratacion >= 60.0) {
        return 1.0;  // Optimal hydration
    } else if (hidratacion >= 10.0) {
        return 0.5 + 0.5 * (hidratacion - 10.0) / 50.0;  // Reduced activity
    } else {
        return 0.3;  // Cryptobiotic state - minimal survival
    }
}

int Tardigrade::calcularSupervivencia() {
    double factorTemp = calcularFactorTemperatura();
    double factorRad = calcularFactorRadiacion();
    double factorPres = calcularFactorPresion();
    double factorHid = calcularFactorHidratacion();
    
    // Combined survival score (weighted average)
    double supervivencia = (factorTemp * 0.3 + factorRad * 0.2 + 
                           factorPres * 0.2 + factorHid * 0.3) * 100.0;
    
    int resultado = static_cast<int>(std::max(0.0, std::min(100.0, supervivencia)));
    
    actualizarEstado(resultado);
    
    return resultado;
}

void Tardigrade::actualizarEstado(int supervivencia) {
    if (supervivencia >= 70) {
        currentState = TardigradeState::ACTIVE;
    } else if (supervivencia >= 30) {
        currentState = TardigradeState::TUN;  // Cryptobiotic state
    } else if (supervivencia >= 10) {
        currentState = TardigradeState::REVIVING;
    } else {
        currentState = TardigradeState::DEAD;
    }
}

std::string Tardigrade::estadoVisual() const {
    switch (currentState) {
        case TardigradeState::ACTIVE:
            return "Activo";
        case TardigradeState::TUN:
            return "Criptobiosis (Tun)";
        case TardigradeState::REVIVING:
            return "Reviviendo";
        case TardigradeState::DEAD:
            return "Muerto";
        default:
            return "Desconocido";
    }
}

TardigradeState Tardigrade::getEstado() const {
    return currentState;
}