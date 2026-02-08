FROM node:18-slim

# Instalamos g++ para compilar el C++
RUN apt-get update && apt-get install -y g++ && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app

# Copiamos archivos de Node
COPY package*.json ./
RUN npm install --production

# Copiamos el resto de archivos (incluyendo DiezusAI.cpp y dataset.txt)
COPY . .

# Compilamos el ejecutable de C++
RUN g++ -O3 DiezusAI.cpp -o DiezusAI -pthread
RUN chmod +x DiezusAI

# Puerto de Render
EXPOSE 3000

CMD ["node", "server.js"]