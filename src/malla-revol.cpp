// Nombre: Ramón

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de las clases 
// **    + MallaRevol: malla indexada de triángulos obtenida por 
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida 
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   using namespace glm ;
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //
   // ............................... 
   unsigned n = num_copias;
   unsigned m = perfil.size();

   // Tabla de vértices
   for (unsigned i=0; i <= n-1; i++){
      float angle = 2*M_PI * i/(n-1);
      // Matriz de rotación respecto al eje y
      mat3 mat_rot = rotate(angle, glm::vec3(0,1,0));

      for (unsigned j=0; j <= m-1; j++){
         glm::vec3 q = mat_rot * perfil[j];
         vertices.push_back(q);
      }
   }

   // Tabla de triángulos
   for (unsigned i=0; i <= n-2; i++)
      for (unsigned j=0; j <= m-2; j++){
         unsigned k = i*m+j;
         triangulos.push_back(glm::uvec3(k, k+m, k+m+1));
         triangulos.push_back(glm::uvec3(k, k+m+1, k+1));
      }


}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   std::vector<glm::vec3> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);
}



// -----------------------------------------------------------------------------



Cilindro::Cilindro
(
      const int num_verts_per, // número de vértices del perfil original (m)
      const unsigned nperfiles // número de perfiles (n)
)
{
   ponerNombre( std::string("malla por revolución del perfil de un Cilindro"));
   std::vector<glm::vec3> perfil;
   
   double dist = 1.0/(num_verts_per-1);

   // Puntos del perfil
   perfil.push_back({1,0,0});
   for (unsigned i=1; i < num_verts_per; i++)
      perfil.push_back({1, perfil[i-1][Y] + dist, 0});

   inicializar(perfil, nperfiles);
}

Cono::Cono
(
      const int num_verts_per, // número de vértices del perfil original (m)
      const unsigned nperfiles // número de perfiles (n)
)
{
   ponerNombre( std::string("malla por revolución del perfil de un Cono"));
   std::vector<glm::vec3> perfil;
   
   double dist = 1.0/(num_verts_per-1);

   // Puntos del perfil
   perfil.push_back({1,0,0});
   for (unsigned i=1; i < num_verts_per; i++)
      perfil.push_back({perfil[i-1][X] - dist, perfil[i-1][Y] + dist, 0});

   inicializar(perfil, nperfiles);
}

Esfera::Esfera
(
      const int num_verts_per, // número de vértices del perfil original (m)
      const unsigned nperfiles // número de perfiles (n)
)
{
   ponerNombre( std::string("malla por revolución del perfil de una Esfera"));
   std::vector<glm::vec3> perfil;

   // Puntos del perfil
   for (unsigned i=0; i < num_verts_per; i++){
      double angle = M_PI*i/(num_verts_per-1) - 0.5*M_PI;
      perfil.push_back({cos(angle), sin(angle), 0});
   }

   inicializar(perfil, nperfiles);
}

