# Clasificador automático de residuos sólidos
Proyecto de Curso: Diseño Mecatrónico

![Render](https://github.com/Bharuck/Mechatronic_Design_Project/blob/main/1.Documentaci%C3%B3n/imgs/Sistema_implementado.png?raw=true)


### Autores:
- Alfred
- Benitez Alonso
- Corcuera Araujo, Carlos Bit
- Huamán Huamán, William Fabián
- Mendoza Pascual, Lady Alexandra
- Rocha Montoya, Carlos Adrian
- Vargas Quiroz, James Anderson Jose Octavio


### Resumen:
En el presente proyecto se desarrolla un contenedor de desechos inteligente, capaz de clasificar los residuos que se introducen dentro, logrando clasificar los desechos hasta en 5 tipos distintos: Papel, plástico, vidrio, metal y orgánicos/otros. El reconocimiento de los residuos se logra gracias a sensores y todo el control es realizado mediante un Arduino Mega 2560.

### Flujo de Funcionamiento:
![Flujograma](https://github.com/Bharuck/Mechatronic_Design_Project/blob/main/1.Documentaci%C3%B3n/imgs/DiagramaDeFlujo.png?raw=true)

### Diagrama Eléctrico:
Como se mencionaba antes, para lograr el reconocimiento de los residuos se utilizaron sensores, .y para accionar el mecanismo se usaron motores nema y servomotores

| Microcontrolador  | Sensores       | actuadores        |
|-------------------|----------------|-------------------|
| Arduino Mega 2560 | S. capacitivo  | 2 Motores Nema 17 |
|                   | S. inductivo   | Servomotor        |
|                   | S. óptico      |                   |
|                   | Celda de carga |                   |
|                   | S. infrarrojo  |                   |
|                   | S. ultrasónico |                   |


A grandes rasgos, el diagrama eléctrico se presenta debajo.

![Conecciones](https://github.com/Bharuck/Mechatronic_Design_Project/blob/main/1.Documentaci%C3%B3n/imgs/DiagramaElectrico.png?raw=true)

### Análisis de esfuerzos:
Para asegurar la fiabilidad del proyecto con respecto a soportar cargas tanto de los componentes como de los mecanismos, se realizó un análisis de esfuerzos mediante Software especializado.

![Conecciones](https://github.com/Bharuck/Mechatronic_Design_Project/blob/main/1.Documentaci%C3%B3n/imgs/An%C3%A1lisis_de_esfuerzos.png?raw=true)