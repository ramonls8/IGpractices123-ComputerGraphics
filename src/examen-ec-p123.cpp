// Nombre: Ramón
#include "examen-ec-p123.h"

// ****************************************************************************
// Clase 'P1MallaPiramide

P1MallaPiramide::P1MallaPiramide()
:  MallaInd( "P1MallaPiramide" )
{

   vertices =
      {  { 0 , 0, 0  }, // 0 (Centro de abajo)
         { 1 , 0, 1  }, // 1
         { 1 , 0, -1 }, // 2
         { -1, 0, -1 }, // 3
         { -1, 0, 1  }, // 4
         { 0 , 2, 0  }, // 5 (Centro de arriba)
      } ;

   triangulos =
      {  {0,1,2},{0,2,3},{0,3,4},{0,4,1}, // Base
         {5,1,2},{5,2,3},{5,3,4},{5,4,1}  // Laterales
      } ;

   col_ver =
      {  { 0.6, 0, 0.1 }, // 0 (Centro de abajo)
         { 1, 1, 0 }, // 1
         { 1, 1, 0 }, // 2
         { 1, 1, 0 }, // 3
         { 1, 1, 0 }, // 4
         { 0, 1, 1 }, // 5 (Centro de arriba)
      } ;
}

// ****************************************************************************

P2Barrido::P2Barrido
(
      unsigned m, // número de vértices del perfil original (m)
      unsigned n  // número de perfiles (n)
)
{
   ponerNombre( std::string("P2Barrido"));
   std::vector<glm::vec3> perfil;

   // Puntos del perfil
   for (unsigned i=0; i < m; i++){
      double angle = M_PI*i/(m-1) - 0.5*M_PI;
      perfil.push_back({cos(angle), sin(angle), 0});
   }

   inicializar(perfil, n);
}

// Crea las copias que queremos de dicho perfil.
void P2Barrido::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias    // número de copias del perfil
)
{
   using namespace glm ;
   
   unsigned n = num_copias;
   unsigned m = perfil.size();

   // Tabla de vértices
   for (unsigned i=0; i <= n-1; i++){
      //mat3 mat_tras = translate(glm::vec3(0,0,i*(-2.0/m)));

      for (unsigned j=0; j <= m-1; j++){
         //glm::vec3 q = mat_tras * perfil[j];
         //vertices.push_back(q);

         vertices.push_back({perfil[j].x, perfil[j].y, perfil[j].z + i*(-2.0/m)});
      }
   }

   // Tabla de triángulos
   for (unsigned i=0; i <= n-2; i++){
      for (unsigned j=0; j <= m-2; j++){
         unsigned k = i*m+j;
         triangulos.push_back(glm::uvec3(k, k+m, k+m+1));
         triangulos.push_back(glm::uvec3(k, k+m+1, k+1));
      }
      // Unimos los vértices iniciales y finales de cada perfil
      unsigned k = i*m;
      triangulos.push_back(glm::uvec3(k, k+m, k+m+m-1));
      triangulos.push_back(glm::uvec3(k, k+m-1, k+m+m-1));
   }
}

// ****************************************************************************

P3Mesa::P3Mesa() {
   ponerNombre( std::string("P3Mesa"));

   const float ANCHO = 0.05;

   matrix_subir_y_bajar = leerPtrMatriz(agregar(glm::mat4(1)));

   // Patas
   NodoGrafoEscena * pata = new NodoGrafoEscena();
   pata->agregar(translate(glm::vec3(1-ANCHO,0,1-ANCHO)));
   pata->agregar(translate(glm::vec3(0,0.5,0)));
   matrix_compresion_patas = pata->leerPtrMatriz(pata->agregar(glm::mat4(1)));
   pata->agregar(scale(glm::vec3(ANCHO, 0.5, ANCHO)));
   pata->agregar(new Cubo());

   NodoGrafoEscena * patas = new NodoGrafoEscena();
   for (unsigned i=0; i<4; i++) {
      patas->agregar(rotate(float(M_PI*0.5), glm::vec3(0,1,0)));
      patas->agregar(pata);
   }
   agregar(patas);

   // Tablero
   NodoGrafoEscena * tablero = new NodoGrafoEscena();
   tablero->agregar(translate(glm::vec3(0,1+ANCHO,0)));
   tablero->agregar(scale(glm::vec3(1, ANCHO, 1)));
   tablero->agregar(new Cubo());

   agregar(tablero);

   // Cubos rotantes
   NodoGrafoEscena * cubo = new NodoGrafoEscena();
   cubo->agregar(translate(glm::vec3(0, 0.25, 0)));
   cubo->agregar(scale(glm::vec3(0.08, 0.25, 0.08)));
   cubo->agregar(new Cubo());

   NodoGrafoEscena * cubo_superior = new NodoGrafoEscena();
   cubo_superior->agregar(translate(glm::vec3(0,2*0.25,0)));
   matrix_rotacion_cubo_superior = cubo_superior->leerPtrMatriz(cubo_superior->agregar(glm::mat4(1)));
   cubo_superior->agregar(cubo);

   NodoGrafoEscena * cubos = new NodoGrafoEscena();
   cubos->agregar(translate(glm::vec3(0,1+2*ANCHO,0)));
   cubos->agregar(cubo);
   cubos->agregar(translate(glm::vec3(0,2*0.25,0)));
   matrix_rotacion_cubo_intermedio = cubos->leerPtrMatriz(cubos->agregar(glm::mat4(1)));
   cubos->agregar(cubo_superior);
   cubos->agregar(cubo);

   agregar(cubos);
}

unsigned P3Mesa::leerNumParametros() const {
   const unsigned NUM_PARAM = 2;
   return NUM_PARAM;
}

void P3Mesa::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){
   switch (iParam) {
      case 0:
         *matrix_compresion_patas = scale(glm::vec3(1, 1 + 0.1*cos(2.0*M_PI * (t_sec/1.3)), 1));
         *matrix_subir_y_bajar = translate(glm::vec3(0, 0.1*cos(2.0*M_PI * (t_sec/1.3)), 0));
         break;
      case 1:
         *matrix_rotacion_cubo_superior   = rotate(float( 0.5*M_PI - 0.5*M_PI*cos(2.0*M_PI*t_sec/0.8)), glm::vec3(0,0,1));
         *matrix_rotacion_cubo_intermedio = rotate(float(-0.5*M_PI + 0.5*M_PI*cos(2.0*M_PI*t_sec/0.8)), glm::vec3(0,0,1));
         break;
   }
}
