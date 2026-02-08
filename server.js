const express = require('express');
const path = require('path');
const { execSync } = require('child_process');
const app = express();

app.use(express.json());
app.use(express.static(__dirname));

app.post('/api/chat', (req, res) => {
    const { mensaje } = req.body;
    if (!mensaje) return res.json({ message: "..." });

    try {
        // Ejecutamos el binario compilado pasando el mensaje como argumento
        const resultado = execSync(`./DiezusAI "${mensaje.replace(/"/g, '\\"')}"`).toString();
        res.json(JSON.parse(resultado));
    } catch (e) {
        console.error("Error en C++:", e);
        res.json({ message: "Lo siento, mi núcleo está procesando mucha información.", sentiment: "neutral", action: "none" });
    }
});

app.post('/api/login', (req, res) => res.json({ success: true }));
app.get('/', (req, res) => res.sendFile(path.join(__dirname, 'Frontend.html')));

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`Servidor en puerto ${PORT}`));