FROM node:18-slim

# Instalamos g++ para compilar el C++ directamente
RUN apt-get update && apt-get install -y g++ make && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app

COPY package*.json ./
RUN npm install

COPY . .

# COMPILACIÓN MANUAL (Sustituye a node-gyp)
RUN g++ -O3 DiezusAI.cpp -o DiezusAI -pthread
RUN chmod +x DiezusAI

EXPOSE 3000

CMD ["node", "server.js"]