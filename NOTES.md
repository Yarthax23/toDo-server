GitHub no es un "museo de proyectos terminados".
Es un historial de tu proceso.


README.md   -> lo que ve alguien por primera vez (para el visitante)  
* Qué es este proyecto?
    * Cómo funciona la estructura básica del protocolo (el mensaje entre cliente y servidor, muy resumido)
    * Saber cómo contribuir (si aplica)
* Cómo se ejecuta?
    * Cómo compilar, cómo correr
* En qué estado está?
* Decisiones técnicas importantes
* Problemas y soluciones

NOTES.md    -> tu cerebro volcado ahí adentro
* Ideas
* Dudas
* Decisiones sin cerrar
* Mini-roadmap
* Cosas para revisar
* Cosas para investigar
* Futuros features
* Un link, un recordatorio, lo que sea

LOG.md      -> el diario del proyecto
* lo que hiciste cada día
* qué rompiste
* qué arreglaste
* qué aprendiste
* mini retrospectivas

DOCS       -> Si el proyecto crece
* descripción detallada del protocolo
* arquitectura del servidor
* diagramas
* justificativos técnicos


Ideas:
* implementar salas
* pensar un pequeño protocolo
* mini-juegos: tirar dado/s, número secreto
* después migrar a Go

Cosas para investigar:
* Convención de Commits. https://www.conventionalcommits.org/es/v1.0.0-beta.3 ; https://github.com/KarmaPulse/git-commit-message-conventions ; https://gist.github.com/qoomon/5dfcdf8eec66a051ecd85625518cfd13 

Dudas: 
* revisar qué modelo de sincronización usar

Futuros features:

Links:

Notas personales:

---



[] Proyecto 1: Chat TCP simple en C

*Fase A Base técnica en C (2-6 semanas)*
1. Chat TCP simple en C
    * sockets
    * cliente/servidor
    * enviar/recibir texto
    * seguridad mínima (validación de input básica)
    * manejo de varios clientes con select/poll o threads
2. Agregar salas + interacción
    * sincronización (mutex, select, poll, epoll)
    * manejo de estructuras de datos
    * protocolito simple de mensajes
3. Mini-juegos dentro del chat
    * adivinar número
    * tirar dados
    * decisiones compartidas
    * empezar a pensar "comandos" dentro del chat

*FASE B Migración a Go (cuando ya fluya C)*  
4. Migrar la lógica principal a Go  
5. Convertirlo en API Rest simple
    * Qué es una API ? Qué es hacer APIs en Go? Qué es una API Rest?  
6. Dockerizar
    * Qué es dockerizar? -> meter programa en contenedor aislado (arrancar viendo tema de contenedores de Sistemas Operativos y su taller)  
7. Agregar auth básica  
8. Tests  
9. Documentación sólida  
10. Más adelante: UI en React (Fase C)