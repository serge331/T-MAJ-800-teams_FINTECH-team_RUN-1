<?php

namespace Database\Seeders;

// use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Database\Factories\AccidentFactory;
use Domain\Accidents\Models\Accident;
use Illuminate\Database\Seeder;

class AccidentsSeeder extends Seeder
{
    /**
     * Seed the application's database.
     */
    public function run(): void
    {
        Accident::factory()->count(100)->create();
    }
}
