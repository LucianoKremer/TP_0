#include "client.h"


int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;
	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger("tp0.log", "C");

	// Usando el logger creado previamente

	// Escribi: "Hola! Soy un log"

	log_info(logger, "Hola! Soy un log");

	
	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config("cliente.config", logger);

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	puerto = config_get_string_value(config, "PUERTO");
	ip = config_get_string_value(config, "IP");
	valor = config_get_string_value(config, "CLAVE");

	// Loggeamos el valor de config

	log_info(logger, "El valor de la clave es: %s", valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);
	
	uint32_t handshake = 1;
	uint32_t result;

	send(conexion, &handshake, sizeof(uint32_t), NULL);
	recv(conexion, &result, sizeof(uint32_t), MSG_WAITALL);

	if(result == -1){
		log_error(logger, "No se pudo realizar el handshake \n");
	}else if (result == 0) {
		log_info(logger, "Handshake realizado con exito \n");
	}

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje(valor, conexion);
	log_info(logger, "Mensaje enviado \n");
	// Armamos y enviamos el paquete
	//paquete(conexion);



	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente

}

t_log* iniciar_logger(char *file, char *process_name)
{ 
	t_log* logger;

	if((logger = log_create(file, process_name, 1, LOG_LEVEL_INFO)) == NULL){
		printf("[ERROR] No se pudo crear el logger,\n");
		exit(1);
	}

	log_info(logger, "Iniciando el logger de %s \n", file);

	return logger;
}

t_config* iniciar_config(char *path, t_log* logger)
{

	t_config* nuevo_config;
	
	if((nuevo_config = config_create(path)) == NULL){
		log_info(logger,"[ERROR] No se pudo crear un nuevo config \n");
		exit(1);
	}
		
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	log_info(logger, "Se esta leyendo la consola \n");

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	while (strcmp(leido, ""))
	{
		log_info(logger, leido);
		leido = readline("> ");
		free(leido);
	}
	// ¡No te olvides de liberar las lineas antes de regresar!
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	config_destroy(config);
	log_destroy(logger);
	close(conexion);
	
}
