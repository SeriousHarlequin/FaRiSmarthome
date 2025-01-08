<template>
    <header>
        <h1>FaRiSmarthome</h1>
        <select v-model="$colorMode.preference">
            <option value="light">Light</option>
            <option value="dark">Dark</option>
            <option value="sepia">Sepia</option>
            <option value="blue">Blue</option>
        </select>
    </header>
</template>

<style>
    select {
        margin-left: auto;
        border-radius: 5px;
    }
</style>
<style scoped>
    h1{
        margin: 1px 1px;
    }
</style>