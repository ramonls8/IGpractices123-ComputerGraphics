// Nombre: Ramón

#include "grafo-escena.h"
#include "malla-revol.h"

// *********************************************************************

class Cruz2D : public MallaInd {
   public:
   Cruz2D();
};

// *********************************************************************

// Figura 2D con la forma del símbolo "^"
class CaretShape2D : public MallaInd {
   public:
   CaretShape2D();
};

// *********************************************************************

class Toro : public MallaRevol
{
   public:
   Toro
   (
      const int num_verts_per,  // número de vértices del perfil original (m)
      const unsigned nperfiles, // número de perfiles (n)
      const double R,           // radio al centro del toro
      const double r            // radio menor
   );
};

// *********************************************************************

// clases mallas indexadas por revolución de un perfil generado proceduralmente

class CilindroCompleto : public MallaRevol
{
   public:
   // Constructor: crea el perfil original y llama a inicializar
   // la base tiene el centro en el origen, el radio y la altura son 1
   CilindroCompleto
   (
      const int num_verts_per, // número de vértices del perfil original (m)
      const unsigned nperfiles // número de perfiles (n)
   ) ;
} ;

// *********************************************************************

class Engranaje : public NodoGrafoEscena {
   public:
   Engranaje(unsigned n, float height); // n es el número de dientes del engranaje
   unsigned leerNumParametros() const;
};

// *********************************************************************

class AnilloConPicos : public NodoGrafoEscena {
   public:
   AnilloConPicos(unsigned n); // n es el número de dientes del anillo
   unsigned leerNumParametros() const;
};

// *********************************************************************

class EngranajeGrande : public NodoGrafoEscena {
   public:
   EngranajeGrande(unsigned n); // n es el número de dientes
   unsigned leerNumParametros() const;
};

// *********************************************************************

class EngranajeConCara : public NodoGrafoEscena {
   private:
   glm::mat4 * matrix_mouth_opening = nullptr;
   glm::mat4 * matrix_eye_opening = nullptr;

   public:
   EngranajeConCara(unsigned n); // n es el número de dientes
   unsigned leerNumParametros() const;
   void actualizarEstadoParametro( const unsigned iParam, const float t_sec );

   // Devuelve las matrices de animacion para que puedan ser usadas en otro NodoGrafoEscena
   // que utilice a esta clase EngranajeConCara
   glm::mat4 * getMatrixMouthOpening();
   glm::mat4 * getMatrixEyeOpening();
};

// *********************************************************************

class Klinklang : public NodoGrafoEscena {
   private:
   glm::mat4 * matrix_mouth_opening = nullptr;
   glm::mat4 * matrix_eye_opening = nullptr;
   glm::mat4 * matrix_rotation_objetos_horizontal = nullptr;
   glm::mat4 * matrix_rotation_engranaje_con_cara = nullptr;
   glm::mat4 * matrix_rotation_engranaje_con_esfera_azul = nullptr;
   glm::mat4 * matrix_rotation_engranaje_grande = nullptr;
   glm::mat4 * matrix_movimiento_general = nullptr;

   public:
   Klinklang();
   unsigned leerNumParametros() const;
   void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
};
