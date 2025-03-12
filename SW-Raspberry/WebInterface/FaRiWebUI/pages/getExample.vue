<template>
  <div>
    <h1>Client IP: {{ ip }}</h1>
    <button @click="fetchTempData">Fetch Temperature</button>
    <p>Temperature: {{ temp }}</p>
  </div>
</template>

<script setup>
import { ref, computed } from 'vue'

// IP fetching (runs once when the component is created)
const { data: ipData } = await useAsyncData('ipData', async () => {
  const response = await fetch('http://127.0.0.1:5000/get_ip')
  const data = await response.json()
  return data.last_sender_ip
})

const ip = computed(() => ipData.value || 'Loading...')

// Reactive temperature variable
const temp = ref('Not fetched yet')

// Function to fetch temperature (can be executed multiple times)
const fetchTempData = async () => {
  try {
    const response = await fetch(`http://${ip.value}/fetchTemp`) //` not '
    const data = await response.text() // Read response as plain text
    console.log('Temperature received:', data)
    temp.value = data // Directly assign the received integer (as a string)
  } catch (err) {
    console.error('Error fetching Temperature:', err)
    temp.value = 'Error fetching Temperature'
  }
}
</script>
