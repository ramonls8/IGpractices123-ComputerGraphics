// Nombre: Ramón

#include "modelo-jer.h"

using namespace glm;

const glm::vec3 COLOR_AZUL(0.3, 0.61, 0.69);
const glm::vec3 COLOR_ROJO(1, 0, 0.3);
const glm::vec3 COLOR_GRIS_OSCURO(0.5, 0.5, 0.5);
const glm::vec3 COLOR_GRIS_INTERMEDIO(0.7, 0.7, 0.7);
const glm::vec3 COLOR_GRIS_CLARO(0.79, 0.79, 0.79);
const glm::vec3 COLOR_NEGRO(0.1, 0.1, 0.1);
const glm::vec3 COLOR_BLANCO(0.95, 0.95, 0.95);

// ****************************************************************************
// Clase 'Cruz2D
Cruz2D::Cruz2D()
:  MallaInd( "Cruz2D" )
{
   vertices =
      {  { 1, 0, 0 }, // 0
         { 2, 0, 0 }, // 1
         { 2, 0, 3 }, // 2
         { 1, 0, 3 }, // 3

         { 3, 0, 1 }, // 4
         { 3, 0, 2 }, // 5
         { 0, 0, 2 }, // 6
         { 0, 0, 1 }, // 7
      } ;

   triangulos =
      {  {0,1,2},{2,3,0},
         {4,5,6},{6,7,4}
      } ;
}

// ****************************************************************************
// Clase 'CaretShape2D
// (Figura 2D con la forma del símbolo "^")
CaretShape2D::CaretShape2D()
:  MallaInd( "CaretShape2D" )
{
   vertices =
      {  { 0, 0, 2 }, // 0
         { 0, 0, 0 }, // 1
         { 2, 0, 0 }, // 2
         { 2, 0, 1 }, // 3
         { 1, 0, 1 }, // 4
         { 1, 0, 2 }, // 5
      } ;

   triangulos =
      {  {0,1,2},{2,3,4},{4,5,0}
      } ;
}

// ****************************************************************************
// Clase 'Toro
Toro::Toro
(
   const int num_verts_per,  // número de vértices del perfil original (m)
   const unsigned nperfiles, // número de perfiles (n)
   const double R,           // radio al centro del toro
   const double r            // radio menor
) 
{
   ponerNombre( std::string("malla por revolución del perfil de un Toro") );

   std::vector<glm::vec3> perfil;

   float distancia_ptos = 2*M_PI/num_verts_per;

   for(unsigned int i = 0; i <= num_verts_per; ++i)
      perfil.push_back( {r*cos(i*distancia_ptos) + R, r*sin(i*distancia_ptos), 0} );

   inicializar(perfil, nperfiles);
}


// ****************************************************************************
// Clase 'CilindroCompleto
CilindroCompleto::CilindroCompleto
(
      const int num_verts_per, // número de vértices del perfil original (m)
      const unsigned nperfiles // número de perfiles (n)
)
{
   ponerNombre( std::string("malla por revolución del perfil de un CilindroCompleto"));
   std::vector<glm::vec3> perfil;
   
   double dist = 1.0/(num_verts_per-1);

   // Puntos del perfil
   perfil.push_back({0,0,0});                            // Punto en el centro inferior
   perfil.push_back({1,0,0});
   for (unsigned i=1; i < num_verts_per; i++)
      perfil.push_back({1, perfil[perfil.size()-1][Y] + dist, 0});
   perfil.push_back({0, perfil[perfil.size()-1][Y], 0}); // Punto en el centro superior

   inicializar(perfil, nperfiles);
}

// ****************************************************************************

Engranaje::Engranaje(unsigned n, float height) {
   ponerNombre( std::string("Engranaje"));

   this->ponerColor(COLOR_GRIS_CLARO);

   // El número de dientes debe ser mayor o igual que 3
   if (n<3)
      n=3;

   // La altura del engranaje debe ser mayor que 0
   assert(height > 0);

   NodoGrafoEscena * diente = new NodoGrafoEscena();
   diente->agregar(translate(glm::vec3(1, 0.5, 0)));
   diente->agregar(scale(glm::vec3(2.5/n, 0.5, 1.7/n)));
   diente->agregar(new Cubo());

   // Aplicamos la altura a todos el engranaje
   agregar(scale(glm::vec3(1, height, 1)));

   for (unsigned i=0; i<n; i++){
      agregar(rotate(float(M_PI*2.0/n), glm::vec3(0,1,0)));
      agregar(diente);
   }

   agregar(new CilindroCompleto(2, 30));
}

unsigned Engranaje::leerNumParametros() const {
   const unsigned NUM_PARAM = 0;
   return NUM_PARAM;
}

// ****************************************************************************

AnilloConPicos::AnilloConPicos(unsigned n) {
   ponerNombre( std::string("AnilloConPicos"));

   this->ponerColor(COLOR_GRIS_CLARO);

   NodoGrafoEscena * pico = new NodoGrafoEscena();
   pico->agregar(translate(glm::vec3(1, 0, 0)));
   pico->agregar(rotate(float(-M_PI/2.0), glm::vec3(0,0,1)));
   pico->agregar(scale(glm::vec3(0.05, 0.22, 0.05)));
   pico->agregar(new Cono(2, 20));


   for (unsigned i=0; i<n; i++){
      agregar(rotate(float(M_PI*2.0/n), glm::vec3(0,1,0)));
      agregar(pico);
   }

   NodoGrafoEscena * anillo = new NodoGrafoEscena();
   anillo->agregar(scale(glm::vec3(1, 2.8, 1)));
   anillo->agregar(new Toro(10, 40, 1, 0.025));
   agregar(anillo);
}

unsigned AnilloConPicos::leerNumParametros() const {
   const unsigned NUM_PARAM = 0;
   return NUM_PARAM;
}

// ****************************************************************************

EngranajeGrande::EngranajeGrande(unsigned n) {
   ponerNombre( std::string("EngranajeGrande"));

   // Añadimos la circunferencia negra que hay destrás y delante del engranaje
   NodoGrafoEscena * circunferencia_negra = new NodoGrafoEscena();
   circunferencia_negra->ponerColor(COLOR_NEGRO);
   circunferencia_negra->agregar(translate(glm::vec3(0, 0.15, 0)));
   circunferencia_negra->agregar(scale(glm::vec3(1, 2.1, 1)));
   circunferencia_negra->agregar(new Toro(8, 30, 0.75, 0.08));
   agregar(circunferencia_negra);

   // Añadimos la figura con forma de "^"
   NodoGrafoEscena * caret_shape = new NodoGrafoEscena();
   caret_shape->ponerColor(COLOR_BLANCO);
   caret_shape->agregar(rotate(float(2.0*M_PI * 2.0/3.0), glm::vec3(0, 1, 0)));
   caret_shape->agregar(translate(glm::vec3(0.57, 0.33, 0)));
   caret_shape->agregar(scale(glm::vec3(0.15, 0.15, 0.15)));
   caret_shape->agregar(rotate(float(M_PI*0.25), glm::vec3(0, 1, 0)));
   caret_shape->agregar(new CaretShape2D());
   agregar(caret_shape);

   // Añadimos el cuadrado negro
   NodoGrafoEscena * cuadrado_negro = new NodoGrafoEscena();
   cuadrado_negro->ponerColor(COLOR_NEGRO);
   cuadrado_negro->agregar(rotate(float(2.0*M_PI * 1.0/3.0), glm::vec3(0, 1, 0)));
   cuadrado_negro->agregar(translate(glm::vec3(0.73, 0.33, 0)));
   cuadrado_negro->agregar(scale(glm::vec3(0.15, 0.01, 0.15)));
   cuadrado_negro->agregar(new Cubo());
   agregar(cuadrado_negro);

   // Añadimos el círculo negro
   NodoGrafoEscena * circulo_negro = new NodoGrafoEscena();
   circulo_negro->ponerColor(COLOR_NEGRO);
   circulo_negro->agregar(translate(glm::vec3(0.73, 0.33, 0)));
   circulo_negro->agregar(scale(glm::vec3(0.15, 0.01, 0.15)));
   circulo_negro->agregar(new CilindroCompleto(2, 15));
   agregar(circulo_negro);

   // Añadimos el círculo azul trasero
   NodoGrafoEscena * circulo_azul_trasero = new NodoGrafoEscena();
   circulo_azul_trasero->ponerColor(COLOR_AZUL);
   circulo_azul_trasero->agregar(translate(glm::vec3(0, -0.01, 0)));
   circulo_azul_trasero->agregar(scale(glm::vec3(0.4, 0.01, 0.4)));
   circulo_azul_trasero->agregar(new CilindroCompleto(2, 20));
   agregar(circulo_azul_trasero);

   // Añadimos el engranaje
   Engranaje * engranaje = new Engranaje(n, 0.3);
   engranaje->ponerColor(COLOR_GRIS_INTERMEDIO);
   agregar(engranaje);
}

unsigned EngranajeGrande::leerNumParametros() const {
   const unsigned NUM_PARAM = 0;
   return NUM_PARAM;
}

// ****************************************************************************

EngranajeConCara::EngranajeConCara(unsigned n) {
   ponerNombre( std::string("EngranajeConCara"));

   // Engranaje
   Engranaje * engranaje = new Engranaje(n, 0.4);
   engranaje->ponerColor(COLOR_GRIS_CLARO);
   agregar(engranaje);

   // Círculo gris oscuro en la parte trasera y delantera del engranaje
   NodoGrafoEscena * circulo_interno_gris = new NodoGrafoEscena();
   circulo_interno_gris->ponerColor(COLOR_GRIS_OSCURO);
   circulo_interno_gris->agregar(translate(glm::vec3(0, -0.01, 0)));
   circulo_interno_gris->agregar(scale(glm::vec3(0.8, 0.42, 0.8)));
   circulo_interno_gris->agregar(new CilindroCompleto(2,30));
   agregar(circulo_interno_gris);

   // Círculo azul en la parte trasera del engranaje
   NodoGrafoEscena * circulo_azul_trasero_pequenio = new NodoGrafoEscena();
   circulo_azul_trasero_pequenio->ponerColor(COLOR_AZUL);
   circulo_azul_trasero_pequenio->agregar(translate(glm::vec3(0, -0.02, 0)));
   circulo_azul_trasero_pequenio->agregar(scale(glm::vec3(0.4, 0.02, 0.4)));
   circulo_azul_trasero_pequenio->agregar(new CilindroCompleto(2,20));
   agregar(circulo_azul_trasero_pequenio);

   // Esfera azul
   NodoGrafoEscena * esfera_azul = new NodoGrafoEscena();
   esfera_azul->ponerColor(COLOR_AZUL);
   esfera_azul->agregar(translate(glm::vec3(0, 0.35, 0)));
   esfera_azul->agregar(scale(glm::vec3(0.38, 0.34, 0.38)));
   esfera_azul->agregar(new Esfera(20, 20));
   agregar(esfera_azul);

   // Cruz
   NodoGrafoEscena * cruz = new NodoGrafoEscena();
   cruz->ponerColor(COLOR_BLANCO);
   cruz->agregar(rotate(float(2*M_PI * 0.3), glm::vec3(0, 1, 0)));
   cruz->agregar(translate(glm::vec3(0, 0.42, 0.385)));
   cruz->agregar(scale(glm::vec3(0.11, 0.11, 0.11)));
   cruz->agregar(new Cruz2D());
   agregar(cruz);

   // Boca
   NodoGrafoEscena * boca = new NodoGrafoEscena();
   boca->ponerColor(COLOR_NEGRO);
   boca->agregar(translate(glm::vec3(0, 0.42, 0.575)));
   boca->agregar(scale(glm::vec3(0.1, 0.02, 0.18)));
   matrix_mouth_opening = boca->leerPtrMatriz(boca->agregar(glm::mat4(1)));
   boca->agregar(new CilindroCompleto(2,20));
   agregar(boca);

   // Ojo
   CilindroCompleto * ojo_pupila = new CilindroCompleto(2, 15);
   CilindroCompleto * ojo_retina = new CilindroCompleto(2, 15);
   ojo_pupila->ponerColor(COLOR_NEGRO);
   ojo_retina->ponerColor(COLOR_BLANCO);

   NodoGrafoEscena * ojo = new NodoGrafoEscena();
   ojo->agregar(translate(glm::vec3(-0.49, 0.42, -0.31)));
   ojo->agregar(scale(glm::vec3(0.18, 0.01, 0.18)));
   matrix_eye_opening = ojo->leerPtrMatriz(ojo->agregar(glm::mat4(1)));
   ojo->agregar(ojo_retina);
   ojo->agregar(translate(glm::vec3(0, 1, 0)));
   ojo->agregar(scale(glm::vec3(0.4, 0.4, 0.4)));
   ojo->agregar(ojo_pupila);
   agregar(ojo);
}

unsigned EngranajeConCara::leerNumParametros() const {
   const unsigned NUM_PARAM = 1;
   return NUM_PARAM;
}

void EngranajeConCara::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){
   switch (iParam) {
      case 0:
         *matrix_mouth_opening = *matrix_eye_opening = scale(glm::vec3(0.9 + 0.1*cos(14*t_sec), 1, cos(4*t_sec)));
   }
}

glm::mat4 * EngranajeConCara::getMatrixMouthOpening(){
   return matrix_mouth_opening;
}
glm::mat4 * EngranajeConCara::getMatrixEyeOpening(){
   return matrix_eye_opening;
}

// ****************************************************************************

Klinklang::Klinklang() {
   ponerNombre( std::string("Klinklang"));

   matrix_movimiento_general = leerPtrMatriz(agregar(glm::mat4(1)));

   // OBJETOS EN HORIZONTAL,
   // es decir, el anillo con picos y el engranaje con la esfera roja
   NodoGrafoEscena * objetos_en_horizontal = new NodoGrafoEscena();
   // Añadimios la rotación de la animación
   matrix_rotation_objetos_horizontal = objetos_en_horizontal->leerPtrMatriz(objetos_en_horizontal->agregar(glm::mat4(1)));
   // Rotación inicial para que encaje con los otros engranajes
   objetos_en_horizontal->agregar(rotate(float(M_PI*0.5), glm::vec3(0,1,0)));
   // Añadimos el anillo con picos
   objetos_en_horizontal->agregar(new AnilloConPicos(6));
   // Añadimos el engranaje
   objetos_en_horizontal->agregar(scale(glm::vec3(0.3, 0.3, 0.3)));
   objetos_en_horizontal->agregar(translate(glm::vec3(0, -0.2, 0)));
   objetos_en_horizontal->agregar(new Engranaje(6, 0.4));
   // Añadimos la esfera roja
   Esfera * esfera_roja = new Esfera(20, 20);
   esfera_roja->ponerColor(COLOR_ROJO);
   objetos_en_horizontal->agregar(translate(glm::vec3(0, 0.2, 0)));
   objetos_en_horizontal->agregar(scale(glm::vec3(0.79, 0.4, 0.79)));
   objetos_en_horizontal->agregar(esfera_roja);

   agregar(objetos_en_horizontal);



   // ENGRANAJE CON CARA
   NodoGrafoEscena * engranaje_con_cara = new NodoGrafoEscena();
   engranaje_con_cara->agregar(translate(glm::vec3(-0.6, 0.9, -0.5)));
   engranaje_con_cara->agregar(rotate(float(0.5*M_PI), glm::vec3(1,0,0)));
   engranaje_con_cara->agregar(scale(glm::vec3(0.3, 0.3, 0.3)));
   // Añadimos la animación de giro
   matrix_rotation_engranaje_con_cara = engranaje_con_cara->leerPtrMatriz(engranaje_con_cara->agregar(glm::mat4(1)));
   // Añadimos el engranaje con cara a este nodo
   EngranajeConCara * engranaje_con_cara_instacia = new EngranajeConCara(6);
   engranaje_con_cara->agregar(engranaje_con_cara_instacia);
   // Guardamos los punteros de las matrices de la clase EngranajeConCara
   matrix_mouth_opening = engranaje_con_cara_instacia->getMatrixMouthOpening();
   matrix_eye_opening = engranaje_con_cara_instacia->getMatrixEyeOpening();

   agregar(engranaje_con_cara);



   // ENGRANAJE CON ESFERA AZUL
   NodoGrafoEscena * engranaje_con_esfera_azul = new NodoGrafoEscena();
   // Añadimos el engranaje con las transformaciones a este y a la esfera
   engranaje_con_esfera_azul->agregar(translate(glm::vec3(0, 0.4, -0.5)));
   engranaje_con_esfera_azul->agregar(rotate(float(0.5*M_PI), glm::vec3(1,0,0)));
   matrix_rotation_engranaje_con_esfera_azul
      = engranaje_con_esfera_azul->leerPtrMatriz(engranaje_con_esfera_azul->agregar(glm::mat4(1)));
   engranaje_con_esfera_azul->agregar(scale(glm::vec3(0.3, 0.3, 0.3)));
   engranaje_con_esfera_azul->agregar(new Engranaje(6, 0.4));
   // Añadimos la esfera con sus transformaciones
   engranaje_con_esfera_azul->agregar(translate(glm::vec3(0, 0.2, 0)));
   engranaje_con_esfera_azul->agregar(scale(glm::vec3(0.8, 0.8, 0.8)));
   Esfera * esfera_azul = new Esfera(20, 20);
   esfera_azul->ponerColor(COLOR_AZUL);
   engranaje_con_esfera_azul->agregar(esfera_azul);

   agregar(engranaje_con_esfera_azul);



   // ENGRANAJE GRANDE
   NodoGrafoEscena * engranaje_grande = new NodoGrafoEscena();
   engranaje_grande->agregar(translate(glm::vec3(0, 0.4, -0.7)));
   engranaje_grande->agregar(rotate(float(0.5*M_PI), glm::vec3(1,0,0)));
   matrix_rotation_engranaje_grande
      = engranaje_grande->leerPtrMatriz(engranaje_grande->agregar(glm::mat4(1)));
   engranaje_grande->agregar(scale(glm::vec3(0.65, 0.65, 0.65)));
   engranaje_grande->agregar(new EngranajeGrande(8));
   agregar(engranaje_grande);
}

unsigned Klinklang::leerNumParametros() const {
   const unsigned NUM_PARAM = 4;
   return NUM_PARAM;
}

void Klinklang::actualizarEstadoParametro( const unsigned iParam, const float t_sec ){
   switch (iParam) {
      case 0:
         *matrix_rotation_engranaje_con_cara
            = *matrix_rotation_objetos_horizontal
            = rotate(float(-M_PI * t_sec), glm::vec3(0,1,0));
         *matrix_rotation_engranaje_con_esfera_azul
            = rotate(float(+M_PI * t_sec), glm::vec3(0,1,0));
         break;
      case 1:
         *matrix_rotation_engranaje_grande
            = rotate(float(-t_sec + cos(2*t_sec)), glm::vec3(0,1,0));
         break;
      case 2:
         *matrix_mouth_opening
            = *matrix_eye_opening
            = scale(glm::vec3(0.9 + 0.1*cos(14*t_sec), 1, cos(4*t_sec)));
         break;
      case 3:
         *matrix_movimiento_general
            = translate(glm::vec3(0, 0.1*sin(t_sec), 0));
         break;
   }
}

// ****************************************************************************