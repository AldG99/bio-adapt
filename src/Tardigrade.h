#ifndef TARDIGRADE_H
#define TARDIGRADE_H

#include <string>

enum class TardigradeState {
    ACTIVE,
    TUN,
    REVIVING,
    DEAD
};

class Tardigrade {
private:
    double temperatura;
    double radiacion;
    double presion;
    double hidratacion;
    TardigradeState currentState;

public:
    Tardigrade();
    
    void setTemperatura(double temp);
    void setRadiacion(double rad);
    void setPresion(double pres);
    void setHidratacion(double hid);
    
    double getTemperatura() const;
    double getRadiacion() const;
    double getPresion() const;
    double getHidratacion() const;
    
    int calcularSupervivencia();
    std::string estadoVisual() const;
    TardigradeState getEstado() const;
    
private:
    double calcularFactorTemperatura() const;
    double calcularFactorRadiacion() const;
    double calcularFactorPresion() const;
    double calcularFactorHidratacion() const;
    void actualizarEstado(int supervivencia);
};

#endif // TARDIGRADE_H