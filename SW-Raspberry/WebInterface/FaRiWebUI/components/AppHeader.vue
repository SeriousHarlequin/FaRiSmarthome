<template>
    <header>
        <h1>FaRiSmarhome</h1>
        <select v-model="$colorMode.preference">
            <option value="light">Light</option>
            <option value="dark">Dark</option>
            <option value="sepia">Sepia</option>
        </select>
    </header>
</template>

<style>
    

    select {
        margin-left: auto;
    }
</style>