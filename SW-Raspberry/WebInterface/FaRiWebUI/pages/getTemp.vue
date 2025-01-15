<template>
  <div>
    <h1>Temperature Data</h1>
    <div v-if="error">{{ error }}</div>
    <div v-else-if="!data">Loading...</div>
    <div v-else>
      <p>Temperature: {{ data }}°C</p>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      data: null,
      error: null
    }
  },
  async mounted() {
    try {
      const response = await fetch('http://192.168.143.84/fetchTemp')
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
  }
}
</script> 
