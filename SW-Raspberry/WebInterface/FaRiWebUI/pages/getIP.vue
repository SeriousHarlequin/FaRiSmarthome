<template>
    <div>
      <div>
        <h1>Temperature Data</h1>
        <div v-if="error">{{ error }}</div>
        <div v-else-if="!data">Loading...</div>
        <div v-else>
          <p>Temperature: {{ data }}°C</p>
        </div>
        <button @click="fetchData">Fetch Temp</button>
      </div>
  
      <div>
        <h1>ESP32 IP Address</h1>
        <p v-if="ip_address">IP: {{ ip_address }}</p>
        <p v-else>No IP address fetched yet</p>
        <button @click="fetchIP">Fetch IP Address</button>
        <div v-if="ip_error">{{ ip_error }}</div>
      </div>
    </div>  
</template>
  
<script>
  export default {
    data() {
      return {
        data: null,
        error: null,
        intervalId: null,
        ip_address: null,
        ip_error: null
      }
    },
    async mounted() {
        await this.fetchIP()
        if (this.ip_address) {
            this.fetchData()
            this.intervalId = setInterval(this.fetchData, 3000) // Fetch data every 5 seconds
        }
    },
    methods: {
    async fetchData() {
        try {
            const response = await fetch('http://${this.ip_address}/fetchTemp')//works if ip matches
            if (!response.ok) {
            throw new Error(`Error: ${response.status} ${response.statusText}`)
            }
            const data = await response.text()
            this.data = data
        } catch (error) {
            if (error.response) {
            // Server responded with a status other than 200 range
            this.error = `Error: ${error.response.status} ${error.response.statusText}`
            } else if (error.request) {
            // Request was made but no response received
            this.error = 'Error: No response received from server'
            } else {
            // Something else happened while setting up the request
            this.error = `Error: ${error.message}`
            }
        }
      },
    async fetchIP() {
        try {
            const response = await fetch('http://localhost:5000/get_ip')
            if (!response.ok) {
            throw new Error(`Error: ${response.status} ${response.statusText}`)
            }
            const data = await response.json()
            this.ip_address = data.last_sender_ip
        } catch (error) {
            if (error.response) {
                // Server responded with a status other than 200 range
                this.ip_error = `Error: ${error.response.status} ${error.response.statusText}`
            } else if (error.request) {
                // Request was made but no response received
                this.ip_error = 'Error: No response received from server'
            } else {
                // Something else happened while setting up the request
                this.ip_error = `Error: ${error.message}`
            }
        }
      }
    }
  }
</script>