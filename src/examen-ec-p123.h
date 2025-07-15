// Nombre: Ramón
#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP
#include "malla-ind.h"
#include "grafo-escena.h"

// --------------------------------------------------------------------- 

class P1MallaPiramide : public MallaInd
{
   public:
      P1MallaPiramide();
};

// --------------------------------------------------------------------- 

class P2Barrido : public MallaInd
{
   private:

   public:

   P2Barrido(unsigned m, unsigned n);

   // Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
   // a partir de un perfil y el número de copias que queremos de dicho perfil.
   void inicializar
   (
      const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
      const unsigned                 num_copias  // número de copias del perfil
   ) ;
} ;

// --------------------------------------------------------------------- 

class P3Mesa : public NodoGrafoEscena {
   private:
   glm::mat4 * matrix_compresion_patas = nullptr;
   glm::mat4 * matrix_subir_y_bajar = nullptr;

   glm::mat4 * matrix_rotacion_cubo_superior = nullptr;
   glm::mat4 * matrix_rotacion_cubo_intermedio = nullptr;

   public:
   P3Mesa();
   unsigned leerNumParametros() const;
   void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
};

#endif