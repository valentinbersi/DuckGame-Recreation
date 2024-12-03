# Documentación ténica

## Diagramas:

## Formato de archivos y protocolo

El protocolo usado es binario, consta de 4 tipos de mensajes diferentes a enviar, dependiendo de la etapa de la comunicacion

**Cliente a Servidor**:
Si el Mensaje es desde el lobby se envia en el siguiente orden:
Un byte Literal 0x0 indicando que es un mensaje de tipo Lobby
Un byte Literal indicando el tipo de request: NEWMATCH (0x0), JOINMATCH (0x1), STARTMATCH (0X2)
Un byte sin signo indicando la cantidad de players (1 o 2 players locales)
Un dos bytes sin signo y en BigEndian para indicar el matchID si es que la request no es de tipo **NEWMATCH**.
Si el mensaje es desde el cliente grafico *(SDL)* se envia tal que:


- Primero se envía un byte literal 0x1 indicando que es un mensaje de tipo 'Game'
- Luego se manda otro byte literal indicando el input presionado, desde 0x0 hasta 0x1E, donde también entran los inputs correspondientes de **cheats** que manejará el cliente
- Por último se manda otro byte literal, 1 para player  y 2 para player 2, que simboliza desde qué jugador local proviene el input

- 