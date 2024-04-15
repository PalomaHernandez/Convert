#!/bin/bash

# Variables y constantes globales
readonly MAN_PATH="${PWD}/man"
readonly MKDIR="$(which mkdir)"
readonly MAN="$(which man)"
readonly GCC="$(which gcc)"
readonly INSTALL="$(which install)"
NAME="convert"
[ "$(which convert)" ] && NAME="convert-base"       # Por si ya existe convert en el sistema (ImageMagick)

# Chequea si el script fue ejecutado con permisos de root
# $1 => Opción que requiere permiso de root
check_root() {
  [ "$(id -u)" -ne 0 ] && echo "ERROR: La opción $1 necesita ser ejecutada con permisos de root" && exit 1
}

# Función que imprime la ayuda por pantalla
usage() {
cat <<END
Uso: $0 [opciones]
Opciones:
  -c, --compile         Genera el archivo ejecutable con la opción -Wall habilitada y lo añade al PATH.
  -i, --install         Instala el programa en el sistema, compilándolo previamente de ser necesario.
  -r, --remove          Desinstala el programa del sistema.
  -m, --man             Muestra el manpage sin necesidad de instalarlo.
  -h, --help            Muestra esta ayuda y sale.
END
}

# Función que compila el proyecto con las dependencias necesarias
compile() {
  local files="${PWD}/src"
  [ -d "${PWD}/bin" ] || mkdir "${PWD}/bin"
  "${GCC}" -Wall "${files}/convertlib.c" "${files}/convert_entero.c" "${files}/convert_fraccionario.c"        \
                 "${files}/convert.c" "${files}/strings.c" -lm -o "${PWD}/bin/${NAME}" &&                     \
                 echo -e ":: Compilación exitosa.\nEl archivo compilado se encuentra en: ${PWD}/bin/${NAME}"
  PATH="${PATH}:${PWD}/bin" && echo "Ya puede probar ${NAME} desde la línea de comandos." &&                  \
    echo -e "Para ver la ayuda del programa ejecute:\n\t${NAME} -h"
}

# Compila el ejecutable de ser necesario, lo instala en alguna ubicación del PATH y genera el manpage
inst() {
  check_root '-i|--install'

  # Instalo binario
  local dest="/bin"
  [ -d "/usr/bin" ] && [[ ":${PATH}:" == *":/usr/bin:"* ]] && dest="/usr/bin"
  [[ ":${PATH}:" != *":/bin:"* ]] && [ "${dest}" == "/bin" ] &&                                           \
    echo "ERROR: Añada /bin o /usr/bin a su PATH e intente nuevamente" &&                                 \
    exit 1
  "${INSTALL}" --target-directory="${dest}" "${PWD}/bin/${NAME}"

  # Instalo manpage
  local man_path="/usr/local/share/man/man1"
  [ ! -d "${man_path}" ] && "${MKDIR}" -p "${man_path}"
  "${INSTALL}" --target-directory="${man_path}" --mode=644 "${MAN_PATH}/${NAME}.1.gz"

  echo ":: Instalación exitosa."
}

# Remueve todo el producto de la instalación en el sistema
remove() {
  check_root '-r|--remove'
  # Chequeo para no borrar lo que no debo :v
  if [ -x "/usr/bin/convert" ]; then
    if ! /usr/bin/convert -v 1>/dev/null; then
      rm -fi /usr/bin/conver /usr/local/share/man/man1/convert.1.gz
    fi
  elif [ -x "/bin/convert" ]; then
    if ! /bin/convert -v 1>/dev/null; then
      rm -fi /bin/convert /usr/local/share/man/man1/convert.1.gz
    fi
  fi
  # convert-base es seguro borrarlo
  if [ -x "/usr/bin/convert-base" ]; then
      rm -fi /usr/bin/convert-base /usr/local/share/man/man1/convert-base.1.gz
  elif [ -x "/bin/convert-base" ]; then
      rm -fi /bin/convert-base /usr/local/share/man/man1/convert-base.1.gz
  fi
  echo "Desinstalación exitosa."
}

# Imprime el manpage sin necesidad de instalarlo en el sistema
manpage() {
  "${MAN}" "${MAN_PATH}/${NAME}.1.gz"
}

error_file=$(mktemp)
GETOPT=$(getopt -o cirmh --long compile,install,remove,man,help -- "$@" 2>"${error_file}")
GETOPT_ERR=$(<"${error_file}")
if [ "${GETOPT_ERR}" ]; then
  sed -i "s/getopt: //g" "${error_file}"
  cat "${error_file}"
  usage
  rm -f "${error_file}"
  exit 1
fi

eval set -- "${GETOPT}"

while true; do
  case "$1" in
    -c | --compile)
      compile
      exit 0
      ;;
    -i | --install)
      [ ! -x "${PWD}/bin/${NAME}" ] && compile
      inst
      exit 0
      ;;
    -r | --remove)
      remove
      exit 0
      ;;
    -m | --man)
      manpage
      exit 0
      ;;
    -h | --help)
      usage
      exit 0
      ;;
    --)
      shift
      break
      ;;
    *)
      usage
      exit 0
      ;;
  esac
done
