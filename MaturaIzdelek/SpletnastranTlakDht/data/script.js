async function fetchData() {
    try {
      const response = await fetch("/data");
      const data = await response.json();
  
      document.getElementById("temperature").textContent = data.temperature.toFixed(2);
      document.getElementById("humidity").textContent = data.humidity.toFixed(2);
      document.getElementById("pressure").textContent = data.pressure.toFixed(2);
  
      document.getElementById("avgTemperature").textContent = data.avgTemperature.toFixed(2);
      document.getElementById("avgHumidity").textContent = data.avgHumidity.toFixed(2);
      document.getElementById("avgPressure").textContent = data.avgPressure.toFixed(2);
    } catch (error) {
      console.error("Napaka pri pridobivanju podatkov:", error);
    }
  }
  
  // Posodobi podatke vsake 2 sekundi
  setInterval(fetchData, 2000);
  fetchData();  // Prvič pridobi podatke