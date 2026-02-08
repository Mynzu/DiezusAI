FROM node:18-bullseye
RUN apt-get update && apt-get install -y build-essential python3
WORKDIR /usr/src/app
COPY package*.json ./
RUN npm install
COPY . .
RUN npx node-gyp rebuild
EXPOSE 3000
CMD [ "node", "server.js" ]