void abrircompuerta() {
  angulo = 0;
  myservo.write(angulo);
  delay(500);

  angulo = 180;
  myservo.write(angulo);
  delay(2000);

  angulo = 0;
  myservo.write(angulo);
  delay(2000);
}

// Función para obtener el peso en gramos
float obtenerPesoEnGramos() {
  float pesoEnGramos = celda.get_units(10);  // Obtiene el valor promedio de 10 lecturas
  celda.power_down();        // apaga el modulo HX711              // demora de 3 segundos
  celda.power_up();          // despierta al modulo HX711
  
  return pesoEnGramos;
}