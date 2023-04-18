Funcion cantViajes ()
	//incremento e inicio son pulsadores
	Repetir 
		Si incremento = 1 Entonces
			numViajes = numViajes + 1
			Escribir numViajes
		Fin Si
	Hasta Que inicio = 1
	
	Si inicio = 1 Entonces
		aceptacion = 1
	Fin Si
Fin Funcion

Funcion cronometro ()
	Si inicioCronometro == 1 Entonces
		seg = seg + 1
		Si seg == 60 Entonces
			min = min + 1
			seg = 0
			Si min = 60 Entonces
				hora = hora + 1
				min = 0
			Fin Si
		Fin Si
	Fin Si
Fin Funcion

Funcion cuentaRegresiva ()
	regresion = 3 - (aux + 1)
	Escribir regresion
	Si regresion <= 0 Entonces
		Escribir ".."
		flagregresion = 2
	Fin Si
Fin Funcion

Funcion juego ()
	Repetir
		numLed = x
	Hasta Que numLed == numLedActual
	
	Segun numLed Hacer
		1:
			Escribir "led 1"
			numLedActual = 1
			activacionJuego = 1
		2:
			Escribir "led 2"
			numLedActual = 2
			activacionJuego = 1
		3:
			Escribir "led 3"
			numLedActual = 3
			activacionJuego = 1
		4:
			Escribir "led 4"
			numLedActual = 4
			activacionJuego = 1
		5:
			Escribir "led 5"
			numLedActual = 5
			activacionJuego = 1
	Fin Segun
Fin Funcion

Funcion finDelJuego ()
	Escribir "Felicidades"
	Escribir "Fin del juego!"
	Escribir "Su tiempo :"
	Escribir hs ":" min ":" seg
Fin Funcion

Algoritmo proyecto
	Si aceptacion==0 Entonces
		Escribir 'Cant de viajes:'
		cantViajes
	SiNo
		Segun flagRegresion Hacer
			0:
				Escribir "El juego inicia en"
				Escribir "cuenta regresiva"
				cuentaregresiva
				flagregresion = 1
			1:
				Timeriniciado = 1 
				// el timer inciia la cuenta regresiva
			2:
				Escribir "A JUGAR!"
				inicioCronometro = 1
				// aca se vuelve a iniciar el timer para que interrumpa a la funcion cronometro
				Si activacionJuego == 0 Entonces
					Escribir "funcion Juego"
				FinSi
				Si infras = HIGH Entonces
					contadorViajes = contadorViajes + 1
					Si contadorViajes < numViajes Entonces
						activacionJuego = 0
					FinSi
					Si contadorViajes >= numViajes  Entonces
						inicioCronometro = 0
						Escribir "funcion finDelJuego"
					FinSi
				FinSi
		FinSegun
	FinSi
FinAlgoritmo
