// Nombre: Ramón

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Declaración de las clases 
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

#ifndef IG_MALLAREVOL_HPP
#define IG_MALLAREVOL_HPP

#include <vector>          // usar std::vector
#include <string>

#include "malla-ind.h"   // declaración de 'Objeto3D'
// ---------------------------------------------------------------------
// clase para mallas indexadas obtenidas a partir de la revolución de un perfil

class MallaRevol : public MallaInd
{
   private:



   protected: //

   MallaRevol() {} // solo usable desde clases derivadas con constructores especificos

   // Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
   // a partir de un perfil y el número de copias que queremos de dicho perfil.
   void inicializar
   (
      const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
      const unsigned                 num_copias  // número de copias del perfil
   ) ;
} ;
// --------------------------------------------------------------------- 



class MallaRevolPLY : public MallaRevol
{
   public:
   MallaRevolPLY( const std::string & nombre_arch,
                  const unsigned nperfiles ) ;
} ;



// ---------------------------------------------------------------------



// clases mallas indexadas por revolución de un perfil generado proceduralmente

class Cilindro : public MallaRevol
{
   public:
   // Constructor: crea el perfil original y llama a inicializar
   // la base tiene el centro en el origen, el radio y la altura son 1
   Cilindro
   (
      const int num_verts_per, // número de vértices del perfil original (m)
      const unsigned nperfiles // número de perfiles (n)
   ) ;
} ;

class Cono : public MallaRevol
{
   public:
   // Constructor: crea el perfil original y llama a inicializar
   // la base tiene el centro en el origen, el radio y altura son 1
   Cono
   (
      const int num_verts_per, // número de vértices del perfil original (m)
      const unsigned nperfiles // número de perfiles (n)
   ) ;
} ;

class Esfera : public MallaRevol
{
   public:
   // Constructor: crea el perfil original y llama a inicializar
   // La esfera tiene el centro en el origen, el radio es la unidad
   Esfera
   (
      const int num_verts_per, // número de vértices del perfil original (M)
      const unsigned nperfiles // número de perfiles (N)
   ) ;
} ;

#endif
